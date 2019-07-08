using System;
using System.Drawing;
using Gtk;

namespace Comando
{
	public abstract class UICommandElement
    {
        public enum InteractionState
        {
            Released,
            Pressed,
            Dragging
        }

        private const float PRE_DRAG_DISTANCE = 15.0f;

		private Point _originLocation = new Point(0, 0);
		private GameConfigButtonDescriptor _commandDescriptor;
        private InteractionState _interactionState = InteractionState.Released;
        private Point _draggingOffset = new Point(0, 0);
        private Point _mousePressedPosition = new Point(0, 0);
        private Gtk.Fixed _parent = null;

        public delegate void OnUICommandElementPressEvent(UICommandElement element, object sender, ButtonReleaseEventArgs args);
		public event OnUICommandElementPressEvent ElementPressEvent = null;

        public GameConfigButtonDescriptor GetCommandDescriptor()
        {
            return _commandDescriptor;
		}

		public UICommandElement(Gtk.Fixed parent, GameConfigButtonDescriptor commandDescriptor)
        {
            _parent = parent;

            _commandDescriptor = commandDescriptor;
		}

        public Gtk.Fixed GetParent()
        {
            return _parent;
        }

        public InteractionState GetInteractionState()
        {
            return _interactionState;
        }

		public void SetLocation(Point newLocation)
		{
			_originLocation = newLocation;
			DoSetLocation();
		}
		protected abstract void DoSetLocation();


		public Point GetLocation()
		{
			return _originLocation;
		}

		public Point GetDragLocation()
		{
            return new Point(_originLocation.X - _draggingOffset.X, _originLocation.Y - _draggingOffset.Y);
		}

		public abstract void Init();
		public abstract void Uninit();
		public virtual void PreOnButtonPressEvent() { }

		[GLib.ConnectBefore]
		protected void OnButtonPressEvent(object sender, ButtonPressEventArgs args)
        {
            if (args.Event.Button == 1)
            {
                PreOnButtonPressEvent();
                SetButtonState(InteractionState.Pressed);
                _mousePressedPosition = MainApp.GetInstance().GetCanvasMousePos();
            }
        }

        [GLib.ConnectBefore]
        protected void OnButtonReleaseEvent(object sender, ButtonReleaseEventArgs args)
        {
			if (_interactionState != InteractionState.Dragging)
			{
            	ElementPressEvent?.Invoke(this, sender, args);
			}
            SetButtonState(InteractionState.Released);
        }

        public void SetButtonState(InteractionState interactionState)
        {
            if (_interactionState == InteractionState.Dragging
                && interactionState == InteractionState.Released)
            {
                DraggingController.GetInstance().SetDraggingElement(null);
            }

            _interactionState = interactionState;

            if (_interactionState == InteractionState.Dragging)
            {
                DraggingController.GetInstance().SetDraggingElement(this);
            }
        }

        public abstract void Refresh();

        public void Update()
        {
            if (GetInteractionState() == InteractionState.Pressed)
            {
                Point mousePos = MainApp.GetInstance().GetCanvasMousePos();

                if (UIUtils.Distance(mousePos, _mousePressedPosition) >= PRE_DRAG_DISTANCE)
                {
                    SetButtonState(InteractionState.Dragging);
                    Point elementLocation = GetLocation();
                    _draggingOffset = new Point(elementLocation.X - mousePos.X, elementLocation.Y - mousePos.Y);
                }
            }
            else if (GetInteractionState() == InteractionState.Dragging)
            {
                Point mousePos = MainApp.GetInstance().GetCanvasMousePos();
                Point buttonFinalPos = new Point(mousePos.X + _draggingOffset.X, mousePos.Y + _draggingOffset.Y);

                SetLocation(buttonFinalPos);
            }

            DoUpdate();
        }

        protected virtual void DoUpdate()
        {

        }

		protected void SetLabelText(Gtk.Label label)
		{
            label.Text = GetCommandDescriptor()._tittle;
        }
    }
}

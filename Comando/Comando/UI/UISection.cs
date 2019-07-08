using System;
using System.Collections.Generic;
using System.Drawing;
using Gtk;

namespace Comando
{
	public class UISection
	{
		public static Point DEFAULT_ORIGIN_POINT = new Point(0, 0);

		private Gtk.Label _label = null;
		private List<UICommandElement> _UIElements = null;
		private UITabPage _parent = null;

		private Point _origin = new Point(0, 0);
		private Point _nextPosition = new Point(0, 0);
		private int _boundaryX = 800;

		Point increment = new Point(170, 50);
		Point incrementSection = new Point(0, 40);
		Point buttonSize = new Point(160, 40);
        
        public UISection(UITabPage parent, GameConfigSectionDescriptor sectionDescriptor, Point origin)
		{
            _parent = parent;
			_origin = origin;
			_UIElements = new List<UICommandElement>();
			AddSection(sectionDescriptor);
		}


		public void SetOriginPosition(Point origin)
		{
			_origin = origin;
		}

		public Point GetOriginPosition()
		{
			return _origin;
		}

		public Point GetNextPosition()
		{
			return _nextPosition;
		}

		private void AddSection(GameConfigSectionDescriptor sectionDescriptor)
        {
            Pango.FontDescription fontDescription = Pango.FontDescription.FromString(UIUtils.SECTION_FONT);
            _label = new Gtk.Label();
            _label.Text = sectionDescriptor._tittle;
            _label.ModifyFont(fontDescription);
			_label.Show();
            _parent.GetCanvas().Add(_label);

			foreach (GameConfigButtonDescriptor buttonDescriptor in sectionDescriptor._buttons)
			{
                AddButton(buttonDescriptor);
			}

			Dispose();
		}

		public void RemoveSection()
		{
            _parent.GetCanvas().Remove(_label);

			foreach (UICommandElement element in _UIElements)
			{
				element.Uninit();
			}
		}

        public List<UICommandElement> GetUIElements()
        {
            return _UIElements;
        }

        public void InsertButtonAt(int targetIndex, UICommandElement uiCommandElement)
        {
            _UIElements.Insert(targetIndex, uiCommandElement);
        }

        public void AddButton(GameConfigButtonDescriptor buttonDescriptor)
		{
			UICommandElement uiElement = null;
			if (buttonDescriptor._type == GameConfigButtonDescriptor.Etype.FixedArgument)
			{
				uiElement = new UICommandButton(_parent.GetCanvas(), buttonDescriptor);
			}
			else if (buttonDescriptor._type == GameConfigButtonDescriptor.Etype.ExposedArgument)
			{
				uiElement = new UICommandExposedArgument(_parent.GetCanvas(), buttonDescriptor);
			}
			else if (buttonDescriptor._type == GameConfigButtonDescriptor.Etype.MultiCommand)
			{
				uiElement = new UICommandSequence(_parent.GetCanvas(), buttonDescriptor);
			}

			uiElement.Init();
			uiElement.ElementPressEvent += OnButtonReleaseEvent;
            _UIElements.Add(uiElement);

			Dispose();
		}

        protected void OnButtonReleaseEvent(UICommandElement element, object sender, ButtonReleaseEventArgs args)
		{
			GameConfigButtonDescriptor commandDescriptor = element.GetCommandDescriptor();

			if (args.Event.Button == 1)
			{
				MainApp.GetInstance().OnButtonPressEvent(commandDescriptor);
			}
			else if (args.Event.Button == 3)
			{
				Gtk.Menu rightButtonMenu = new Gtk.Menu();

				Gtk.MenuItem menuItem = new Gtk.MenuItem("Remove command");
				menuItem.ButtonReleaseEvent += OnRemoveCommandButtonPressed;
				menuItem.Data.Add("UICommandElement", element);
				rightButtonMenu.Append(menuItem);

				menuItem = new Gtk.MenuItem("Edit command");
				menuItem.ButtonReleaseEvent += OnEditCommandButtonPressed;
				menuItem.Data.Add("UICommandElement", element);
				rightButtonMenu.Append(menuItem);

				rightButtonMenu.ShowAll();
				rightButtonMenu.Popup();
			}
		}
        
		private void OnRemoveCommandButtonPressed(object sender, ButtonReleaseEventArgs e)
		{
			Gtk.MenuItem sourceMenuOption = Utils.static_cast<Gtk.MenuItem>(sender);
			UICommandElement uiCommandElement = Utils.dynamic_cast<UICommandElement>(sourceMenuOption.Data["UICommandElement"]);
			GameConfigButtonDescriptor commandDescriptor = uiCommandElement.GetCommandDescriptor();

			_UIElements.Remove(uiCommandElement);
			uiCommandElement.Uninit();

            _parent.OnRemoveCommandButtonPressed(commandDescriptor);
		}

		private void OnEditCommandButtonPressed(object sender, ButtonReleaseEventArgs e)
		{
			Gtk.MenuItem sourceMenuOption = Utils.static_cast<Gtk.MenuItem>(sender);
            object commandElementData = sourceMenuOption.Data["UICommandElement"];
            UICommandElement uiCommandElement = Utils.dynamic_cast<UICommandElement>(commandElementData);
			GameConfigButtonDescriptor commandDescriptor = uiCommandElement.GetCommandDescriptor();

            _parent.OnEditCommandButtonPressed(uiCommandElement, commandDescriptor);
		}


        private bool IsElementInsideTargetBoundaries(UICommandElement element, Point target)
        {
            return IsPointInsideTargetBoundaries(element.GetDragLocation(), target);
        }

        private bool IsPointInsideTargetBoundaries(Point point, Point target)
        {
            if (   point.X >= target.X
                && point.X < target.X + increment.X
                && point.Y >= target.Y
                && point.Y < target.Y + increment.Y)

            {
                return true;
            }

            return false;
        }

		public bool IsPointInside(Point point)
		{
			if (point.X >= _origin.X
				&& point.X < _boundaryX
				&& point.Y >= _origin.Y
				&& point.Y < _nextPosition.Y)
			{
				return true;
			}

			return false;
		}

        public int GetElementIndex(Point targetPoint)
        {
            int count = 0;
            Point nextPosition = _origin;
            nextPosition.Y += incrementSection.Y;

            foreach (UICommandElement element in _UIElements)
            {
                if (IsPointInsideTargetBoundaries(targetPoint, nextPosition))
                {
                    return count;
                }

                nextPosition.X += increment.X;
                if (nextPosition.X > _boundaryX)
                {
                    nextPosition.X = _origin.X;
                    nextPosition.Y += increment.Y;
                }

                ++count;
            }

            return -1;
        }

        public void Dispose()
		{
			bool isIntersecting = false;
			_nextPosition = _origin;
			UIUtils.SetWidgetPosition(_parent.GetCanvas(), _label, _nextPosition);
			_nextPosition.Y += incrementSection.Y;

            UICommandElement dragElement = DraggingController.GetInstance().GetDraggedElement();
            foreach (UICommandElement element in _UIElements)
			{
                if (dragElement != null)
                {
                    if (element == dragElement)
                    {
                        continue;
                    }
					if (!isIntersecting && IsElementInsideTargetBoundaries(dragElement, _nextPosition))
                    {
						isIntersecting = true;
                        _nextPosition.X += increment.X;
                        if (_nextPosition.X > _boundaryX)
                        {
                            _nextPosition.X = _origin.X;
                            _nextPosition.Y += increment.Y;
                        }
                    }
                }

                element.SetLocation(_nextPosition);

                _nextPosition.X += increment.X;
				if (_nextPosition.X > _boundaryX)
				{
					_nextPosition.X = _origin.X;
					_nextPosition.Y += increment.Y;
				}
			}

			_nextPosition.X = _origin.X;
			_nextPosition.Y += increment.Y;
		}

		public void Update()
		{
			foreach (UICommandElement element in _UIElements)
			{
				element.Update();
			}

            if(DraggingController.GetInstance().IsDragging())
            {
                Dispose();
            }
		}
	}
}
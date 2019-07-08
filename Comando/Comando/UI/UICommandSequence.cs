using System;
using System.Drawing;
using Gtk;

namespace Comando
{
	public class UICommandSequence : UICommandElement
	{
		private Gtk.Button _button = null;
		private Point _buttonSize = new Point(160, 40);

        public UICommandSequence(Gtk.Fixed parent, GameConfigButtonDescriptor commandDescriptor)
		    : base(parent, commandDescriptor)
		{
        }

        public override void Init()
        {
            Gtk.Label label = new Gtk.Label();
            Pango.FontDescription fontDescription = Pango.FontDescription.FromString(UIUtils.BUTTON_FONT);
            label.ModifyFont(fontDescription);
            label.ShowAll();

            _button = new Gtk.Button(label);
			_button.CanFocus = true;
			_button.UseUnderline = true;
			_button.TooltipText = GetCommandDescriptor()._command;
			_button.WidthRequest = _buttonSize.X;
			_button.HeightRequest = _buttonSize.Y;
			_button.Show();
            _button.ButtonPressEvent += OnButtonPressEvent;
            _button.ButtonReleaseEvent += OnButtonReleaseEvent;
            GetParent().Add(_button);

			Refresh();
		}

		public override void Uninit()
		{
            GetParent().Remove(_button);
		}

		protected override void DoSetLocation()
		{
			UIUtils.SetWidgetPosition(GetParent(), _button, GetLocation());
		}

		public override void Refresh()
		{
			Gtk.Label label = (Gtk.Label)_button.Child;
			SetLabelText(label);
		}
	}
}


// This file has been generated by the GUI designer. Do not modify.
namespace Comando
{
	public partial class WidgetSequenceCommandEntry
	{
		private global::Gtk.Fixed fixed1;

		private global::Gtk.Entry _inputCommand;

		private global::Gtk.Button button1;

		private global::Gtk.Button _commandPickerButton;

		private global::Gtk.Entry _inputArguments;

		protected virtual void Build()
		{
			global::Stetic.Gui.Initialize(this);
			// Widget Comando.WidgetSequenceCommandEntry
			global::Stetic.BinContainer.Attach(this);
			this.Name = "Comando.WidgetSequenceCommandEntry";
			// Container child Comando.WidgetSequenceCommandEntry.Gtk.Container+ContainerChild
			this.fixed1 = new global::Gtk.Fixed();
			this.fixed1.Name = "fixed1";
			this.fixed1.HasWindow = false;
			// Container child fixed1.Gtk.Fixed+FixedChild
			this._inputCommand = new global::Gtk.Entry();
			this._inputCommand.WidthRequest = 200;
			this._inputCommand.CanFocus = true;
			this._inputCommand.Name = "_inputCommand";
			this._inputCommand.Text = global::Mono.Unix.Catalog.GetString(" ");
			this._inputCommand.IsEditable = true;
			this._inputCommand.InvisibleChar = '●';
			this.fixed1.Add(this._inputCommand);
			// Container child fixed1.Gtk.Fixed+FixedChild
			this.button1 = new global::Gtk.Button();
			this.button1.HeightRequest = 25;
			this.button1.CanFocus = true;
			this.button1.Name = "button1";
			global::Gtk.Image w2 = new global::Gtk.Image();
			w2.Pixbuf = global::Stetic.IconLoader.LoadIcon(this, "gtk-cancel", global::Gtk.IconSize.Menu);
			this.button1.Image = w2;
			this.fixed1.Add(this.button1);
			global::Gtk.Fixed.FixedChild w3 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this.button1]));
			w3.X = 450;
			// Container child fixed1.Gtk.Fixed+FixedChild
			this._commandPickerButton = new global::Gtk.Button();
			this._commandPickerButton.WidthRequest = 30;
			this._commandPickerButton.HeightRequest = 25;
			this._commandPickerButton.CanFocus = true;
			this._commandPickerButton.Name = "_commandPickerButton";
			this._commandPickerButton.UseUnderline = true;
			global::Gtk.Image w4 = new global::Gtk.Image();
			w4.Pixbuf = global::Stetic.IconLoader.LoadIcon(this, "gtk-find", global::Gtk.IconSize.Button);
			this._commandPickerButton.Image = w4;
			this.fixed1.Add(this._commandPickerButton);
			global::Gtk.Fixed.FixedChild w5 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this._commandPickerButton]));
			w5.X = 202;
			// Container child fixed1.Gtk.Fixed+FixedChild
			this._inputArguments = new global::Gtk.Entry();
			this._inputArguments.WidthRequest = 150;
			this._inputArguments.CanFocus = true;
			this._inputArguments.Name = "_inputArguments";
			this._inputArguments.IsEditable = true;
			this._inputArguments.InvisibleChar = '●';
			this.fixed1.Add(this._inputArguments);
			global::Gtk.Fixed.FixedChild w6 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this._inputArguments]));
			w6.X = 250;
			this.Add(this.fixed1);
			if ((this.Child != null))
			{
				this.Child.ShowAll();
			}
			this.Hide();
			this.button1.Clicked += new global::System.EventHandler(this.OnDeleteEntryButtonClick);
			this._commandPickerButton.Clicked += new global::System.EventHandler(this.OnCommandPickerButtonClick);
		}
	}
}

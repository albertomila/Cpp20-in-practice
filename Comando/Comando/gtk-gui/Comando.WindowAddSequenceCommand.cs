
// This file has been generated by the GUI designer. Do not modify.
namespace Comando
{
	public partial class WindowAddSequenceCommand
	{
		private global::Gtk.Fixed fixed4;

		private global::Gtk.Label _labelTittle;

		private global::Gtk.Label _labelCommandTittle1;

		private global::Gtk.Entry _inputTitle;

		private global::Gtk.Button _buttonAccept;

		private global::Gtk.Label _labelCommand;

		private global::Gtk.Label _labelArguments;

		private global::Gtk.ScrolledWindow GtkScrolledWindow;

		private global::Gtk.Fixed _inputContainer;

		private global::Gtk.Button _buttonAddEntry;

		protected virtual void Build()
		{
			global::Stetic.Gui.Initialize(this);
			// Widget Comando.WindowAddSequenceCommand
			this.Name = "Comando.WindowAddSequenceCommand";
			this.Title = global::Mono.Unix.Catalog.GetString("WindowAddSequenceCommand");
			this.WindowPosition = ((global::Gtk.WindowPosition)(4));
			// Container child Comando.WindowAddSequenceCommand.Gtk.Container+ContainerChild
			this.fixed4 = new global::Gtk.Fixed();
			this.fixed4.Name = "fixed4";
			this.fixed4.HasWindow = false;
			// Container child fixed4.Gtk.Fixed+FixedChild
			this._labelTittle = new global::Gtk.Label();
			this._labelTittle.Name = "_labelTittle";
			this._labelTittle.LabelProp = global::Mono.Unix.Catalog.GetString("New sequence command");
			this.fixed4.Add(this._labelTittle);
			global::Gtk.Fixed.FixedChild w1 = ((global::Gtk.Fixed.FixedChild)(this.fixed4[this._labelTittle]));
			w1.X = 8;
			w1.Y = 7;
			// Container child fixed4.Gtk.Fixed+FixedChild
			this._labelCommandTittle1 = new global::Gtk.Label();
			this._labelCommandTittle1.Name = "_labelCommandTittle1";
			this._labelCommandTittle1.LabelProp = global::Mono.Unix.Catalog.GetString("Tittle");
			this.fixed4.Add(this._labelCommandTittle1);
			global::Gtk.Fixed.FixedChild w2 = ((global::Gtk.Fixed.FixedChild)(this.fixed4[this._labelCommandTittle1]));
			w2.X = 10;
			w2.Y = 30;
			// Container child fixed4.Gtk.Fixed+FixedChild
			this._inputTitle = new global::Gtk.Entry();
			this._inputTitle.CanFocus = true;
			this._inputTitle.Name = "_inputTitle";
			this._inputTitle.IsEditable = true;
			this._inputTitle.InvisibleChar = '●';
			this.fixed4.Add(this._inputTitle);
			global::Gtk.Fixed.FixedChild w3 = ((global::Gtk.Fixed.FixedChild)(this.fixed4[this._inputTitle]));
			w3.X = 7;
			w3.Y = 46;
			// Container child fixed4.Gtk.Fixed+FixedChild
			this._buttonAccept = new global::Gtk.Button();
			this._buttonAccept.WidthRequest = 150;
			this._buttonAccept.HeightRequest = 40;
			this._buttonAccept.CanFocus = true;
			this._buttonAccept.Name = "_buttonAccept";
			this._buttonAccept.UseUnderline = true;
			this._buttonAccept.Label = global::Mono.Unix.Catalog.GetString("Accept");
			this.fixed4.Add(this._buttonAccept);
			global::Gtk.Fixed.FixedChild w4 = ((global::Gtk.Fixed.FixedChild)(this.fixed4[this._buttonAccept]));
			w4.X = 8;
			w4.Y = 309;
			// Container child fixed4.Gtk.Fixed+FixedChild
			this._labelCommand = new global::Gtk.Label();
			this._labelCommand.Name = "_labelCommand";
			this._labelCommand.LabelProp = global::Mono.Unix.Catalog.GetString("Command");
			this.fixed4.Add(this._labelCommand);
			global::Gtk.Fixed.FixedChild w5 = ((global::Gtk.Fixed.FixedChild)(this.fixed4[this._labelCommand]));
			w5.X = 26;
			w5.Y = 78;
			// Container child fixed4.Gtk.Fixed+FixedChild
			this._labelArguments = new global::Gtk.Label();
			this._labelArguments.Name = "_labelArguments";
			this._labelArguments.LabelProp = global::Mono.Unix.Catalog.GetString("Arguments");
			this.fixed4.Add(this._labelArguments);
			global::Gtk.Fixed.FixedChild w6 = ((global::Gtk.Fixed.FixedChild)(this.fixed4[this._labelArguments]));
			w6.X = 272;
			w6.Y = 75;
			// Container child fixed4.Gtk.Fixed+FixedChild
			this.GtkScrolledWindow = new global::Gtk.ScrolledWindow();
			this.GtkScrolledWindow.WidthRequest = 500;
			this.GtkScrolledWindow.HeightRequest = 200;
			this.GtkScrolledWindow.Name = "GtkScrolledWindow";
			this.GtkScrolledWindow.ShadowType = ((global::Gtk.ShadowType)(1));
			// Container child GtkScrolledWindow.Gtk.Container+ContainerChild
			global::Gtk.Viewport w7 = new global::Gtk.Viewport();
			w7.ShadowType = ((global::Gtk.ShadowType)(0));
			// Container child GtkViewport.Gtk.Container+ContainerChild
			this._inputContainer = new global::Gtk.Fixed();
			this._inputContainer.WidthRequest = 450;
			this._inputContainer.HeightRequest = 100;
			this._inputContainer.Name = "_inputContainer";
			this._inputContainer.HasWindow = false;
			// Container child _inputContainer.Gtk.Fixed+FixedChild
			this._buttonAddEntry = new global::Gtk.Button();
			this._buttonAddEntry.CanFocus = true;
			this._buttonAddEntry.Name = "_buttonAddEntry";
			global::Gtk.Image w8 = new global::Gtk.Image();
			w8.Pixbuf = global::Stetic.IconLoader.LoadIcon(this, "gtk-add", global::Gtk.IconSize.Menu);
			this._buttonAddEntry.Image = w8;
			this._inputContainer.Add(this._buttonAddEntry);
			global::Gtk.Fixed.FixedChild w9 = ((global::Gtk.Fixed.FixedChild)(this._inputContainer[this._buttonAddEntry]));
			w9.X = 8;
			w9.Y = 6;
			w7.Add(this._inputContainer);
			this.GtkScrolledWindow.Add(w7);
			this.fixed4.Add(this.GtkScrolledWindow);
			global::Gtk.Fixed.FixedChild w12 = ((global::Gtk.Fixed.FixedChild)(this.fixed4[this.GtkScrolledWindow]));
			w12.X = 12;
			w12.Y = 102;
			this.Add(this.fixed4);
			if ((this.Child != null))
			{
				this.Child.ShowAll();
			}
			this.DefaultWidth = 534;
			this.DefaultHeight = 387;
			this.Show();
			this._buttonAccept.Clicked += new global::System.EventHandler(this.OnAddNewSequenceCommandButtonClick);
			this._buttonAddEntry.Clicked += new global::System.EventHandler(this.OnAddEntryButtonPress);
		}
	}
}

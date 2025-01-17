
// This file has been generated by the GUI designer. Do not modify.
namespace Comando
{
	public partial class WidgetHostTargetEntry
	{
		private global::Gtk.Fixed fixed3;

		private global::Gtk.Entry _inputHostTarget;

		private global::Gtk.Button _buttonRemove;

		private global::Gtk.Button button1;

		private global::Gtk.Label _labelConnectionStatus;

		protected virtual void Build()
		{
			global::Stetic.Gui.Initialize(this);
			// Widget Comando.WidgetHostTargetEntry
			global::Stetic.BinContainer.Attach(this);
			this.Name = "Comando.WidgetHostTargetEntry";
			// Container child Comando.WidgetHostTargetEntry.Gtk.Container+ContainerChild
			this.fixed3 = new global::Gtk.Fixed();
			this.fixed3.Name = "fixed3";
			this.fixed3.HasWindow = false;
			// Container child fixed3.Gtk.Fixed+FixedChild
			this._inputHostTarget = new global::Gtk.Entry();
			this._inputHostTarget.WidthRequest = 250;
			this._inputHostTarget.HeightRequest = 27;
			this._inputHostTarget.CanFocus = true;
			this._inputHostTarget.Name = "_inputHostTarget";
			this._inputHostTarget.IsEditable = true;
			this._inputHostTarget.InvisibleChar = '●';
			this.fixed3.Add(this._inputHostTarget);
			// Container child fixed3.Gtk.Fixed+FixedChild
			this._buttonRemove = new global::Gtk.Button();
			this._buttonRemove.CanFocus = true;
			this._buttonRemove.Name = "_buttonRemove";
			this._buttonRemove.UseUnderline = true;
			global::Gtk.Image w2 = new global::Gtk.Image();
			w2.Pixbuf = global::Stetic.IconLoader.LoadIcon(this, "gtk-cancel", global::Gtk.IconSize.Menu);
			this._buttonRemove.Image = w2;
			this.fixed3.Add(this._buttonRemove);
			global::Gtk.Fixed.FixedChild w3 = ((global::Gtk.Fixed.FixedChild)(this.fixed3[this._buttonRemove]));
			w3.X = 250;
			// Container child fixed3.Gtk.Fixed+FixedChild
			this.button1 = new global::Gtk.Button();
			this.button1.CanFocus = true;
			this.button1.Name = "button1";
			this.button1.UseUnderline = true;
			global::Gtk.Image w4 = new global::Gtk.Image();
			w4.Pixbuf = global::Stetic.IconLoader.LoadIcon(this, "gtk-refresh", global::Gtk.IconSize.Menu);
			this.button1.Image = w4;
			this.fixed3.Add(this.button1);
			global::Gtk.Fixed.FixedChild w5 = ((global::Gtk.Fixed.FixedChild)(this.fixed3[this.button1]));
			w5.X = 275;
			// Container child fixed3.Gtk.Fixed+FixedChild
			this._labelConnectionStatus = new global::Gtk.Label();
			this._labelConnectionStatus.Name = "_labelConnectionStatus";
			this._labelConnectionStatus.LabelProp = global::Mono.Unix.Catalog.GetString("Not connected");
			this.fixed3.Add(this._labelConnectionStatus);
			global::Gtk.Fixed.FixedChild w6 = ((global::Gtk.Fixed.FixedChild)(this.fixed3[this._labelConnectionStatus]));
			w6.X = 312;
			w6.Y = 5;
			this.Add(this.fixed3);
			if ((this.Child != null))
			{
				this.Child.ShowAll();
			}
			this.Show();
			this._buttonRemove.Clicked += new global::System.EventHandler(this.OnRemoveHostTargetButtonPress);
			this.button1.Clicked += new global::System.EventHandler(this.OnUpdateConnectionButtonPress);
		}
	}
}

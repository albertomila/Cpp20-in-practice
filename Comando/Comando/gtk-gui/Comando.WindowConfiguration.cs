
// This file has been generated by the GUI designer. Do not modify.
namespace Comando
{
	public partial class WindowConfiguration
	{
		private global::Gtk.Fixed fixed2;

		private global::Gtk.Entry _inputPort;

		private global::Gtk.Entry _inputService;

		private global::Gtk.Entry _inputTarget;

		private global::Gtk.Entry _inputTargetCommand;

		private global::Gtk.Label _labelTargetCommand;

		private global::Gtk.Label _labelTarget;

		private global::Gtk.Label _labelService;

		private global::Gtk.Label _labelPort;

		private global::Gtk.Button _buttonAccept;

		private global::Gtk.Entry _defaultIP;

		private global::Gtk.Label _labelDefaultIP;

		protected virtual void Build()
		{
			global::Stetic.Gui.Initialize(this);
			// Widget Comando.WindowConfiguration
			this.Name = "Comando.WindowConfiguration";
			this.Title = global::Mono.Unix.Catalog.GetString("WindowConfiguration");
			this.WindowPosition = ((global::Gtk.WindowPosition)(4));
			// Container child Comando.WindowConfiguration.Gtk.Container+ContainerChild
			this.fixed2 = new global::Gtk.Fixed();
			this.fixed2.Name = "fixed2";
			this.fixed2.HasWindow = false;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._inputPort = new global::Gtk.Entry();
			this._inputPort.CanFocus = true;
			this._inputPort.Name = "_inputPort";
			this._inputPort.IsEditable = true;
			this._inputPort.InvisibleChar = '●';
			this.fixed2.Add(this._inputPort);
			global::Gtk.Fixed.FixedChild w1 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._inputPort]));
			w1.X = 131;
			w1.Y = 7;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._inputService = new global::Gtk.Entry();
			this._inputService.CanFocus = true;
			this._inputService.Name = "_inputService";
			this._inputService.IsEditable = true;
			this._inputService.InvisibleChar = '●';
			this.fixed2.Add(this._inputService);
			global::Gtk.Fixed.FixedChild w2 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._inputService]));
			w2.X = 131;
			w2.Y = 39;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._inputTarget = new global::Gtk.Entry();
			this._inputTarget.CanFocus = true;
			this._inputTarget.Name = "_inputTarget";
			this._inputTarget.IsEditable = true;
			this._inputTarget.InvisibleChar = '●';
			this.fixed2.Add(this._inputTarget);
			global::Gtk.Fixed.FixedChild w3 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._inputTarget]));
			w3.X = 132;
			w3.Y = 70;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._inputTargetCommand = new global::Gtk.Entry();
			this._inputTargetCommand.CanFocus = true;
			this._inputTargetCommand.Name = "_inputTargetCommand";
			this._inputTargetCommand.IsEditable = true;
			this._inputTargetCommand.InvisibleChar = '●';
			this.fixed2.Add(this._inputTargetCommand);
			global::Gtk.Fixed.FixedChild w4 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._inputTargetCommand]));
			w4.X = 131;
			w4.Y = 102;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._labelTargetCommand = new global::Gtk.Label();
			this._labelTargetCommand.Name = "_labelTargetCommand";
			this._labelTargetCommand.LabelProp = global::Mono.Unix.Catalog.GetString("Target command");
			this.fixed2.Add(this._labelTargetCommand);
			global::Gtk.Fixed.FixedChild w5 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._labelTargetCommand]));
			w5.X = 31;
			w5.Y = 107;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._labelTarget = new global::Gtk.Label();
			this._labelTarget.Name = "_labelTarget";
			this._labelTarget.LabelProp = global::Mono.Unix.Catalog.GetString("Target");
			this.fixed2.Add(this._labelTarget);
			global::Gtk.Fixed.FixedChild w6 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._labelTarget]));
			w6.X = 31;
			w6.Y = 75;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._labelService = new global::Gtk.Label();
			this._labelService.Name = "_labelService";
			this._labelService.LabelProp = global::Mono.Unix.Catalog.GetString("Service");
			this.fixed2.Add(this._labelService);
			global::Gtk.Fixed.FixedChild w7 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._labelService]));
			w7.X = 31;
			w7.Y = 43;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._labelPort = new global::Gtk.Label();
			this._labelPort.Name = "_labelPort";
			this._labelPort.LabelProp = global::Mono.Unix.Catalog.GetString("Port");
			this.fixed2.Add(this._labelPort);
			global::Gtk.Fixed.FixedChild w8 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._labelPort]));
			w8.X = 31;
			w8.Y = 13;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._buttonAccept = new global::Gtk.Button();
			this._buttonAccept.WidthRequest = 150;
			this._buttonAccept.HeightRequest = 40;
			this._buttonAccept.CanFocus = true;
			this._buttonAccept.Name = "_buttonAccept";
			this._buttonAccept.UseUnderline = true;
			this._buttonAccept.Label = global::Mono.Unix.Catalog.GetString("Accept");
			this.fixed2.Add(this._buttonAccept);
			global::Gtk.Fixed.FixedChild w9 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._buttonAccept]));
			w9.X = 29;
			w9.Y = 183;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._defaultIP = new global::Gtk.Entry();
			this._defaultIP.CanFocus = true;
			this._defaultIP.Name = "_defaultIP";
			this._defaultIP.IsEditable = true;
			this._defaultIP.InvisibleChar = '●';
			this.fixed2.Add(this._defaultIP);
			global::Gtk.Fixed.FixedChild w10 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._defaultIP]));
			w10.X = 131;
			w10.Y = 133;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this._labelDefaultIP = new global::Gtk.Label();
			this._labelDefaultIP.Name = "_labelDefaultIP";
			this._labelDefaultIP.LabelProp = global::Mono.Unix.Catalog.GetString("Default IP");
			this.fixed2.Add(this._labelDefaultIP);
			global::Gtk.Fixed.FixedChild w11 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this._labelDefaultIP]));
			w11.X = 32;
			w11.Y = 138;
			this.Add(this.fixed2);
			if ((this.Child != null))
			{
				this.Child.ShowAll();
			}
			this.DefaultWidth = 311;
			this.DefaultHeight = 267;
			this.Show();
			this._buttonAccept.Clicked += new global::System.EventHandler(this.OnWindowAcceptButtonPressed);
		}
	}
}

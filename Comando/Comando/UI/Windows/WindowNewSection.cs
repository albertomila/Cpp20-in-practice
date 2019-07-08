using System;
namespace Comando
{
	public partial class WindowNewSection : Gtk.Window
    {
        private UITabPage _parent = null;
        private int _sectionIndex = 0;

		public WindowNewSection(UITabPage parent, int sectionIndex) :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
            _parent = parent;
            _sectionIndex = sectionIndex;
		}

		public string GetTittle()
		{
			return _inputName.Text;
		}

		public int GetSectionIndex()
		{
			return _sectionIndex;
		}

		[GLib.ConnectBefore]
		protected void OnAddNewSectionButtonPress(object o, Gtk.ButtonReleaseEventArgs args)
		{
            _parent.OnAddNewSectionButtonAcceptPress();
		}
	}
}

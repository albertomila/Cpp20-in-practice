using System;
using System.Collections.Generic;
using System.Collections;

namespace Comando
{
	public partial class WindowCommandList : Gtk.Window
	{
		public delegate void OnCommandPicked(string command);
		public event OnCommandPicked OnCommandPickedEvent = null;

		private string _selectedCommand = string.Empty;

		public WindowCommandList() :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();

			Gtk.TreeViewColumn column1 = new Gtk.TreeViewColumn();
			column1.Title = "Name";
			column1.MinWidth = 100;
			_commandsTree.AppendColumn(column1);
			Gtk.CellRendererText column1Renderer = new Gtk.CellRendererText();
			column1.PackStart (column1Renderer, true);
			column1.AddAttribute (column1Renderer, "text", 0);

			Gtk.TreeViewColumn column2 = new Gtk.TreeViewColumn();
			column2.Title = "Description";
			_commandsTree.AppendColumn(column2);
			Gtk.CellRendererText column2Renderer = new Gtk.CellRendererText();
			column2.PackStart (column2Renderer, true);
			column2.AddAttribute (column2Renderer, "text", 1);

			Gtk.ListStore lstore = new Gtk.ListStore(typeof(string), typeof(string));
			_commandsTree.Model = lstore;

			List<KeyValuePair<string, string>> commandsSorted = new List<KeyValuePair<string, string>>();
			Dictionary<string, string> commands = MainApp.GetInstance().GetCommands().GetCommands();
            foreach (KeyValuePair<string, string> keyCommand in commands)
            {
                commandsSorted.Add(keyCommand);
            }
			commandsSorted.Sort((keyPair1, keyPair2) => string.Compare(keyPair1.Key, keyPair2.Key));
			foreach (KeyValuePair<string, string> commandPair in commandsSorted)
			{
				lstore.AppendValues(commandPair.Key, commandPair.Value);
			}

			_commandsTree.CursorChanged += OnCursorChanged;
			_commandsTree.Show();
		}

		void OnCursorChanged(object sender, EventArgs e)
		{
			Gtk.TreeView treeView = Utils.dynamic_cast<Gtk.TreeView>(sender);
			Gtk.TreeSelection selection = treeView.Selection;
			Gtk.TreeModel treeModel = null;
			Gtk.TreeIter treeIter;
			selection.GetSelected(out treeModel, out treeIter);
			_selectedCommand = treeModel.GetValue(treeIter, 0).ToString();
		}

		public void Update()
		{
			if (_selectedCommand != string.Empty)
			{
				OnCommandPickedEvent?.Invoke(_selectedCommand);
			}
		}
	}
}

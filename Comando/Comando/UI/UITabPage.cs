using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Gtk;
using System.Drawing;

namespace Comando
{
    public class UITabPage
    {
        private Gtk.Fixed _canvas = null;
        private Gtk.ScrolledWindow _scrolledWindow = null;
        private Gtk.Viewport _viewport = null;
        private Gtk.Label _label = null;

        private GameConfigDB _gameConfigDB = null;
        private List<UISection> _uiSections = null;
        private Point _mouseRightClickPoint = new Point(0, 0);

        private WindowAddSingleCommand _windowAddSingleCommand = null;
        private WindowAddExposedCommand _windowAddExposedCommand = null;
        private WindowAddSequenceCommand _windowAddSequenceCommand = null;
        private WindowNewSection _windowAddNewSection = null;
        private WindowPrompt _windowPrompt = null;

        public delegate void OnTabPageCallback(UITabPage tabPage);
        public event OnTabPageCallback OnDeleteTabAcceptEvent = null;
        public event OnTabPageCallback OnTabSelectedEvent = null;

        public UITabPage
            ( GameConfigDB gameConfigDB
            , Gtk.ScrolledWindow scrolledWindow
            , Gtk.Viewport viewport
            , Gtk.Label label
            , Gtk.Fixed canvas)
        {
            _scrolledWindow = scrolledWindow;
            _viewport = viewport;
            _label = label;
            _canvas = canvas;
            _canvas.ScrollEvent += OnScrollEvent;
			_scrolledWindow.ButtonPressEvent += OnMainWindowButtonPressed;
            _label.Parent.ButtonPressEvent += OnTabButtonPressed;

            _gameConfigDB = gameConfigDB;
            _uiSections = new List<UISection>();

            Point currentSectionPoint = UISection.DEFAULT_ORIGIN_POINT;
            foreach (GameConfigSectionDescriptor sectionDescriptor in _gameConfigDB.GetSections())
            {
                UISection newSection = new UISection(this, sectionDescriptor, currentSectionPoint);
                currentSectionPoint = newSection.GetNextPosition();
                _uiSections.Add(newSection);
            }

            ResizeCanvas();
        }

        public GameConfigDB GetGameConfig()
        {
            return _gameConfigDB;
        }

        public Gtk.Fixed GetCanvas()
        {
            return _canvas;
        }

        private void OnScrollEvent(object o, ScrollEventArgs args)
        {
            RefreshCanvas();
        }

        public Point GetCanvasMousePos()
        {
            int outX = 0;
            int outY = 0;
            GetCanvas().GetPointer(out outX, out outY);
            return new Point(outX, outY);
        }

        private Point GetMouseRightClickCanvasPos()
        {
            return _mouseRightClickPoint;
        }

		public void InitDropEvent()
		{
			DraggingController.GetInstance().ClearEvents();
			DraggingController.GetInstance().OnDropEvent += OnDropUIElement;
		}

        [GLib.ConnectBefore]
        protected void OnTabButtonPressed(object o, ButtonPressEventArgs args)
        {
            if (args.Event.Button == 1)
            {
				DraggingController.GetInstance().ClearEvents();
            	DraggingController.GetInstance().OnDropEvent += OnDropUIElement;

                OnTabSelectedEvent?.Invoke(this);
            }
            else if (args.Event.Button == 3)
            {
                _mouseRightClickPoint = GetCanvasMousePos();

                Gtk.Menu rightButtonMenu = new Gtk.Menu();

                Gtk.MenuItem menuItem = null;

                menuItem = new Gtk.MenuItem("Delete tab page");
				menuItem.ButtonReleaseEvent += OnDeleteTabPagePressed;
                rightButtonMenu.Append(menuItem);
                rightButtonMenu.ShowAll();
                rightButtonMenu.Popup();
            }
        }

        [GLib.ConnectBefore]
        protected void OnMainWindowButtonPressed(object o, ButtonPressEventArgs args)
        {
            if (args.Event.Button == 3)
            {
                _mouseRightClickPoint = GetCanvasMousePos();

                Gtk.Menu rightButtonMenu = new Gtk.Menu();

                Gtk.MenuItem menuItem = null;

                if (_uiSections.Count == 0)
                {
                    menuItem = new Gtk.MenuItem("Add new section");
                    menuItem.ButtonReleaseEvent += OnMainWindowAddNewSectionPressed;
                    rightButtonMenu.Append(menuItem);
                }
                else if (_uiSections.Count > 0)
                {
                    menuItem = new Gtk.MenuItem("Add command");
                    menuItem.ButtonReleaseEvent += OnMainWindowAddCommandPressed;
                    rightButtonMenu.Append(menuItem);

                    menuItem = new Gtk.MenuItem("Add command sequence");
                    menuItem.ButtonReleaseEvent += OnMainWindowAddCommandSequencePressed;
                    rightButtonMenu.Append(menuItem);

                    menuItem = new Gtk.MenuItem("Add command exposed argument");
                    menuItem.ButtonReleaseEvent += OnMainWindowAddCommandExposedArgPressed;
                    rightButtonMenu.Append(menuItem);

                    menuItem = new Gtk.MenuItem("Add new section");
                    menuItem.ButtonReleaseEvent += OnMainWindowAddNewSectionPressed;
                    rightButtonMenu.Append(menuItem);

                    menuItem = new Gtk.MenuItem("Remove section");
                    menuItem.ButtonReleaseEvent += OnMainWindowRemoveSectionPressed;
                    rightButtonMenu.Append(menuItem);
                }

                rightButtonMenu.ShowAll();
                rightButtonMenu.Popup();
            }
        }

        private void OnDeleteTabPagePressed(object sender, ButtonReleaseEventArgs e)
        {
			UIUtils.ShutDownWindowSafe(ref _windowPrompt);
            _windowPrompt = new WindowPrompt("Are you sure to delete this tab and all its content?");
            _windowPrompt.OnAcceptEvent += OnDeleteTabAccept;
            _windowPrompt.OnCancelEvent += OnClosePrompt;
            MoveWindowToWindowPos(_windowPrompt);
            _windowPrompt.Show();
        }

        private void OnDeleteTabAccept()
        {
            UIUtils.ShutDownWindow(ref _windowPrompt);

            OnDeleteTabAcceptEvent?.Invoke(this);
        }

        private void OnMainWindowAddCommandPressed(object sender, ButtonReleaseEventArgs e)
        {
            Point canvasMousePos = GetMouseRightClickCanvasPos();
            int sectionIndex = GetMousePosSectionIndex(canvasMousePos);
            OnMenuAddNewCommandButtonPress(sender, e, GameConfigButtonDescriptor.Etype.FixedArgument, sectionIndex);
        }

        private void OnMainWindowAddCommandExposedArgPressed(object sender, ButtonReleaseEventArgs e)
        {
            Point canvasMousePos = GetMouseRightClickCanvasPos();
            int sectionIndex = GetMousePosSectionIndex(canvasMousePos);
            OnMenuAddNewCommandButtonPress(sender, e, GameConfigButtonDescriptor.Etype.ExposedArgument, sectionIndex);
        }

        private void OnMainWindowAddCommandSequencePressed(object sender, ButtonReleaseEventArgs e)
        {
            Point canvasMousePos = GetMouseRightClickCanvasPos();
            int sectionIndex = GetMousePosSectionIndex(canvasMousePos);
            OnMenuAddNewCommandButtonPress(sender, e, GameConfigButtonDescriptor.Etype.MultiCommand, sectionIndex);
        }

        public void AddNewButton(GameConfigButtonDescriptor buttonDescriptor, int sectionIndex)
        {
            UISection sectionSelected = _uiSections[sectionIndex];
            sectionSelected.AddButton(buttonDescriptor);
            RefreshCanvas();
        }

		public void AddNewSection(GameConfigSectionDescriptor sectionDescriptor, int previousSectionIndex)
        {
            Point newSectionOriginPoint = UISection.DEFAULT_ORIGIN_POINT;
            if (_uiSections.Count > 0)
            {
                newSectionOriginPoint = _uiSections[previousSectionIndex].GetNextPosition();
            }

            UISection newSection = new UISection(this, sectionDescriptor, newSectionOriginPoint);

            if (previousSectionIndex < _uiSections.Count - 1)
            {
                _uiSections.Insert(previousSectionIndex + 1, newSection);
            }
            else
            {
                _uiSections.Add(newSection);
            }
            RefreshCanvas();
        }

		public void AddNewSection(GameConfigSectionDescriptor sectionDescriptor)
		{
			Point newSectionOriginPoint = UISection.DEFAULT_ORIGIN_POINT;
			if (_uiSections.Count > 0)
			{
				newSectionOriginPoint = _uiSections[_uiSections.Count - 1].GetNextPosition();
			}

			UISection newSection = new UISection(this, sectionDescriptor, newSectionOriginPoint);
			_uiSections.Add(newSection);
			RefreshCanvas();
        }

        public int GetMousePosSectionIndex(Point mousePos)
        {
            int sectionIndex = 0;
            for (int i = 0; i < _uiSections.Count; ++i)
            {
                if (_uiSections[i].IsPointInside(mousePos))
                {
                    break;
                }

                if (i < _uiSections.Count - 1)
                {
                    ++sectionIndex;
                }
            }

            return sectionIndex;
        }

        private void OnMainWindowAddNewSectionPressed(object sender, ButtonReleaseEventArgs e)
        {
            Point canvasMousePos = GetMouseRightClickCanvasPos();
            int sectionIndex = GetMousePosSectionIndex(canvasMousePos);
            OnAddNewSectionButtonPress(sectionIndex);
        }

        private void OnMainWindowRemoveSectionPressed(object sender, ButtonReleaseEventArgs e)
        {
            Point canvasMousePos = GetMouseRightClickCanvasPos();
            int sectionIndex = GetMousePosSectionIndex(canvasMousePos);

            RemoveSection(sectionIndex);
        }

        public void OnRemoveSectionAccept(int sectionIndex)
        {
            _uiSections[sectionIndex].RemoveSection();
            _uiSections.RemoveAt(sectionIndex);
            RefreshCanvas();
        }


        public void RefreshCanvas()
        {
            Point currentSectionPoint = UISection.DEFAULT_ORIGIN_POINT;
            foreach (UISection section in _uiSections)
            {
                section.SetOriginPosition(currentSectionPoint);
                section.Dispose();
                currentSectionPoint = section.GetNextPosition();
            }
            ResizeCanvas();
        }

        private void ResizeCanvas()
        {
            if (_uiSections.Count > 0)
            {
                GetCanvas().HeightRequest = _uiSections[_uiSections.Count - 1].GetNextPosition().Y;
            }
        }

        public void OnMenuAddNewCommandButtonPress(object sender, EventArgs e, GameConfigButtonDescriptor.Etype type, int sectionIndex)
        {
			UIUtils.ShutDownWindowSafe(ref _windowAddSingleCommand);
			UIUtils.ShutDownWindowSafe(ref _windowAddExposedCommand);
			UIUtils.ShutDownWindowSafe(ref _windowAddSequenceCommand);
            if (type == GameConfigButtonDescriptor.Etype.FixedArgument)
            {
                _windowAddSingleCommand = new WindowAddSingleCommand(this, sectionIndex);
                MoveWindowToWindowPos(_windowAddSingleCommand);
                _windowAddSingleCommand.Show();
            }
            else if (type == GameConfigButtonDescriptor.Etype.ExposedArgument)
            {
                _windowAddExposedCommand = new WindowAddExposedCommand(this, sectionIndex);
                MoveWindowToWindowPos(_windowAddExposedCommand);
                _windowAddExposedCommand.Show();
            }
            else if (type == GameConfigButtonDescriptor.Etype.MultiCommand)
            {
                _windowAddSequenceCommand = new WindowAddSequenceCommand(this, sectionIndex);
                MoveWindowToWindowPos(_windowAddSequenceCommand);
                _windowAddSequenceCommand.Show();
            }
        }

        public void OnEditCommandButtonPressed(UICommandElement uiCommandElement, GameConfigButtonDescriptor commandDescriptor)
        {
			UIUtils.ShutDownWindowSafe(ref _windowAddSingleCommand);
			UIUtils.ShutDownWindowSafe(ref _windowAddExposedCommand);
			UIUtils.ShutDownWindowSafe(ref _windowAddSequenceCommand);
            if (commandDescriptor._type == GameConfigButtonDescriptor.Etype.FixedArgument)
            {
                _windowAddSingleCommand = new WindowAddSingleCommand(this, uiCommandElement, commandDescriptor);
                MoveWindowToWindowPos(_windowAddSingleCommand);
                _windowAddSingleCommand.Show();
            }
            else if (commandDescriptor._type == GameConfigButtonDescriptor.Etype.ExposedArgument)
            {
                _windowAddExposedCommand = new WindowAddExposedCommand(this, uiCommandElement, commandDescriptor);
                MoveWindowToWindowPos(_windowAddExposedCommand);
                _windowAddExposedCommand.Show();
            }
            else if (commandDescriptor._type == GameConfigButtonDescriptor.Etype.MultiCommand)
            {
                _windowAddSequenceCommand = new WindowAddSequenceCommand(this, uiCommandElement, commandDescriptor);
                MoveWindowToWindowPos(_windowAddSequenceCommand);
                _windowAddSequenceCommand.Show();
            }
        }

        public void OnAddNewCommandButtonPress(string tittle, string command, string arguments, int sectionIndex)
        {
            UIUtils.ShutDownWindow(ref _windowAddSingleCommand);
            GameConfigButtonDescriptor newButtonDescriptor = _gameConfigDB.AddNewCommand
                      (GameConfigButtonDescriptor.Etype.FixedArgument
                      , tittle
                      , command
                      , arguments
                      , sectionIndex);
            AddNewButton(newButtonDescriptor, sectionIndex);
        }

        public void OnAddNewCommandButtonPress(string tittle, string command, int sectionIndex)
        {
            UIUtils.ShutDownWindow(ref _windowAddExposedCommand);
            GameConfigButtonDescriptor newButtonDescriptor = _gameConfigDB.AddNewCommand
                      (GameConfigButtonDescriptor.Etype.ExposedArgument
                      , tittle
                      , command
                      , string.Empty
                      , sectionIndex);
            AddNewButton(newButtonDescriptor, sectionIndex);
        }

        public void OnEditSingleCommandButtonPress(UICommandElement uiCommandElement, GameConfigButtonDescriptor buttonDescriptor, string tittle, string command, string arguments)
        {
            UIUtils.ShutDownWindow(ref _windowAddSingleCommand);

            buttonDescriptor._tittle = tittle;
            buttonDescriptor._command = command;
            buttonDescriptor._arguments = arguments;
            uiCommandElement.Refresh();
        }

        public void OnEditExposedCommandButtonPress(UICommandElement uiCommandElement, GameConfigButtonDescriptor buttonDescriptor, string tittle, string command, string arguments)
        {
            UIUtils.ShutDownWindow(ref _windowAddExposedCommand);
            buttonDescriptor._tittle = tittle;
            buttonDescriptor._command = command;
            buttonDescriptor._arguments = arguments;
            uiCommandElement.Refresh();
        }

        public void OnAddNewSequenceCommandButtonClick(string tittle, List<KeyValuePair<string, string>> commandList, int sectionIndex)
        {
            UIUtils.ShutDownWindow(ref _windowAddSequenceCommand);
            GameConfigButtonDescriptor newButtonDescriptor = _gameConfigDB.AddNewSequenceCommand
                      (GameConfigButtonDescriptor.Etype.MultiCommand
                      , tittle
                         , commandList
                      , sectionIndex);
            AddNewButton(newButtonDescriptor, sectionIndex);
        }

        public void OnEditSequenceCommandButtonPress
                        (UICommandElement uiCommandElement
                         , GameConfigButtonDescriptor buttonDescriptor
                         , string tittle
                         , List<KeyValuePair<string, string>> commandList)
        {
            UIUtils.ShutDownWindow(ref _windowAddSequenceCommand);
            buttonDescriptor._tittle = tittle;
            buttonDescriptor.AddSequenceCommand(commandList);

            uiCommandElement.Refresh();
        }

        public void OnRemoveCommandButtonPressed(GameConfigButtonDescriptor commandDescriptor)
        {
            _gameConfigDB.RemoveCommand(commandDescriptor);
            RefreshCanvas();
        }

        public void OnAddNewSectionButtonPress(int sectionIndex)
        {
			UIUtils.ShutDownWindowSafe(ref _windowAddNewSection);
            _windowAddNewSection = new WindowNewSection(this, sectionIndex);
            MoveWindowToWindowPos(_windowAddNewSection);
            _windowAddNewSection.Show();
        }

        public void OnAddNewSectionButtonAcceptPress()
        {
            string tittle = _windowAddNewSection.GetTittle();
            int sectionIndex = _windowAddNewSection.GetSectionIndex();

            GameConfigSectionDescriptor newSection = _gameConfigDB.AddNewSection(tittle, sectionIndex);
            AddNewSection(newSection, sectionIndex);

            UIUtils.ShutDownWindow(ref _windowAddNewSection);
        }

        public void RemoveSection(int sectionIndex)
        {
			UIUtils.ShutDownWindowSafe(ref _windowPrompt);
            GameConfigSectionDescriptor sectionToDelete = _gameConfigDB.GetSection(sectionIndex);
            _windowPrompt = new WindowPrompt("Are you sure to delete section \"" + sectionToDelete._tittle + "\" and all its content ?");
            _windowPrompt.SetExternalData(sectionIndex);
            _windowPrompt.OnAcceptEvent += OnRemoveSectionAccept;
            _windowPrompt.OnCancelEvent += OnClosePrompt;
            MoveWindowToWindowPos(_windowPrompt);
            _windowPrompt.Show();
        }

        public void OnRemoveSectionAccept()
        {
            int sectionIndex = Utils.static_cast<int>(_windowPrompt.GetExternalData());

            _gameConfigDB.RemoveSection(sectionIndex);

            OnRemoveSectionAccept(sectionIndex);
            UIUtils.ShutDownWindow(ref _windowPrompt);
        }

        public void OnClosePrompt()
        {
            UIUtils.ShutDownWindow(ref _windowPrompt);
        }

        private void MoveWindowToWindowPos(Gtk.Window window)
        {
            MainApp.GetInstance().MoveWindowToWindowPos(window);
        }

		public void Update()
		{
			foreach (UISection section in _uiSections)
			{
				section.Update();
			}
		}

        public int GetNearestSectionIndex(Point targetPoint)
        {
            double minDistance = double.MaxValue;

            int nearestSectionIndex = 0;
            for(int i = 0; i < _uiSections.Count; ++i)
            {
                UISection section = _uiSections[i];
                double distance = UIUtils.Distance(targetPoint, section.GetOriginPosition());
                if (distance < minDistance)
                {
                    minDistance = distance;
                    nearestSectionIndex = i;
                }
            }

            return nearestSectionIndex;
        }

        public void OnDropUIElement(UICommandElement uiCommandElement)
        {
            GameConfigButtonDescriptor commandDescriptor = uiCommandElement.GetCommandDescriptor();

            int currentSectionIndex = 0;
            //remove it from UI
            foreach (UISection section in _uiSections)
            {
                if(section.GetUIElements().Exists(element => element == uiCommandElement))
                {
                    section.GetUIElements().Remove(uiCommandElement);
                    ++currentSectionIndex;
                    break;
                }
            }

            //remove it from DataBase
            _gameConfigDB.RemoveCommand(commandDescriptor);
            
            //find target section and position
            int sectionIndex = 0;
            UISection sectionTarget = null;
            Point commandLocation = uiCommandElement.GetDragLocation();
            foreach (UISection section in _uiSections)
            {
				if(section.IsPointInside(commandLocation))
                {
                    sectionTarget = section;
                    break;
                }

                ++sectionIndex;
            }

            if(sectionTarget == null)
            {
                sectionIndex = GetNearestSectionIndex(commandLocation);
                sectionTarget = _uiSections[sectionIndex];
            }

            int elementIndex = sectionTarget.GetElementIndex(commandLocation);
            if (elementIndex < 0 )
            {
                elementIndex = sectionTarget.GetUIElements().Count;
            }

            //add it to UI
            sectionTarget.InsertButtonAt(elementIndex, uiCommandElement);

            //add it to DataBase
            _gameConfigDB.AddCommandAtLocation(commandDescriptor, sectionIndex, elementIndex);
            
            RefreshCanvas();
        }
    }
}

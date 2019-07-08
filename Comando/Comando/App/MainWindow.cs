using System;
using System.Collections;
using System.Collections.Generic;
using Gtk;
using System.Drawing;
namespace Comando
{
	public partial class MainWindow : Gtk.Window
	{
		private WindowAddTab _windowAddTab = null;
		private WindowPrompt _windowPrompt = null;

		private bool _isRunning = false;

		public bool IsRunning()
		{
			return _isRunning;
		}

	    public MainWindow()
			: base(Gtk.WindowType.Toplevel)
		{
			Build();

	        LoadAllTabs();

	        CreatePageHelperAdd();
			_isRunning = true;
       		this.DeleteEvent += Handle_DeleteEvent;
			this.Title = "Comando, send custom commands to multiple devices";
	    }

		void Handle_DeleteEvent (object o, DeleteEventArgs args)
		{
			_isRunning = false;
		}

		private void LoadAllTabs()
	    {
	        List<GameConfigDB> gameConfigs = MainApp.GetInstance().GetConfig().GetGameConfigs();
	        foreach(GameConfigDB gameConfigDB in gameConfigs)
	        {
	            CreateNewTab(gameConfigDB, true);
	        }

			SelectFirstTab();
	    }

		private void SelectFirstTab()
		{
			if (notebook1.NPages > 0)
			{
				notebook1.Page = 0;
				UITabPage firstTab = GetCurrentTabPage();
				firstTab.InitDropEvent();
			}
		}

	    private void CreateNewTab(GameConfigDB gameConfigDB, bool isInitializing = false)
	    {
	        UITabPage uiTabPage = UITabPageCreator.CreateUICanvasTab(notebook1, gameConfigDB, isInitializing);
	        uiTabPage.OnDeleteTabAcceptEvent += OnDeleteTabAccept;
	        uiTabPage.OnTabSelectedEvent += OnTabSelected;
	    }

	    public UITabPage GetCurrentTabPage()
		{
			Widget currentPage = notebook1.GetNthPage(notebook1.Page);
			object data = currentPage.Data["UITabPage"];
			if (data != null)
			{
				UITabPage tabPage = Utils.static_cast<UITabPage>(data);
				return tabPage;
			}

			return null;
		}

	    private void OnTabSelected(UITabPage tabPage)
	    {
	        int pages = notebook1.NPages;
	        for (int i = 0; i < pages; ++i)
	        {
	            Widget currentPage = notebook1.GetNthPage(i);
	            UITabPage currentTabPage = Utils.static_cast<UITabPage>(currentPage.Data["UITabPage"]);
	            if (currentTabPage == tabPage)
	            {
	                notebook1.Page = i;
	                return;
	            }
	        }
	    }

	    private void OnDeleteTabAccept(UITabPage tabPage)
	    {
	        int pages = notebook1.NPages;
	        for(int i = 0; i<pages; ++i)
	        {
	            Widget currentPage = notebook1.GetNthPage(i);
	            UITabPage currentTabPage = Utils.static_cast<UITabPage>(currentPage.Data["UITabPage"]);
	            if(currentTabPage == tabPage)
	            {
	                notebook1.RemovePage(i);
	                if(i > 0)
	                {
	                    notebook1.Page = i - 1;
	                }

	                GamesConfigLoader gamesConfigLoader = MainApp.GetInstance().GetConfig().GetGameConfig();
	                gamesConfigLoader.DeleteGameConfig(currentTabPage.GetGameConfig());
	                return;
	            }
	        }
	    }

	    private void CreatePageHelperAdd()
	    {
	        UITabPageCreator.CreateUICanvasButtonAddTab(this, notebook1, OnAddNewTabButtonPressed);
	    }

	    [GLib.ConnectBefore]
	    private void OnAddNewTabButtonPressed(object sender, ButtonReleaseEventArgs e)
	    {
			if (_windowAddTab != null)
			{
            	UIUtils.ShutDownWindow(ref _windowAddTab);
			}

	        if(notebook1.NPages < UITabPageCreator.MAX_TABS)
	        {
				UIUtils.ShutDownWindowSafe(ref _windowAddTab);
				_windowAddTab = new WindowAddTab();
				_windowAddTab.OnAcceptButtonPressEvent += OnNewTabAcceptButtonPressed;
				_windowAddTab.Show();
				MainApp.GetInstance().MoveWindowToWindowPos(_windowAddTab);
	        }
	    }

		private void OnNewTabAcceptButtonPressed(string tabName)
        {
            UIUtils.ShutDownWindow(ref _windowAddTab);

	        GamesConfigLoader gamesConfigLoader = MainApp.GetInstance().GetConfig().GetGameConfig();
	        GameConfigDB newGameConfig = gamesConfigLoader.AddNewGameConfig(tabName);
	        CreateNewTab(newGameConfig);
		}

		public void Uptade()
		{
	        UITabPage uiTabPage = GetCurrentTabPage();
	        if(uiTabPage != null)
	        {
				uiTabPage.Update();
	        }
		}

		protected void OnDeleteEvent(object sender, DeleteEventArgs a)
		{
			Application.Quit();
			a.RetVal = true;
		}

		protected void OnMenuConfigurationButtonPress(object sender, EventArgs e)
		{
			MainApp.GetInstance().OnMenuConfigurationButtonPress(sender, e);
		}

		protected void OnMenuAddHostTargetButtonPress(object sender, EventArgs e)
		{
			MainApp.GetInstance().OnOpenWindowAddTargetButtonPress();
	    }

	    protected void OnMenuSaveButtonClick(object sender, EventArgs e)
		{
			MainApp.GetInstance().GetConfig().Save();
		}

		public WidgetConsole GetConsole()
		{
			return _widgetconsole;
		}

		protected void OnExportCommandsButtonPress(object sender, EventArgs e)
		{
			Gtk.FileChooserDialog fileChooser = new Gtk.FileChooserDialog 
				("Choose files"
				 ,this
				 , FileChooserAction.SelectFolder
				 , "Select"
				 , ResponseType.Accept
				 , "Cancel"
				 , ResponseType.Close);
			int response = fileChooser.Run();
            if (response == Utils.static_cast<int>(ResponseType.Close))
            {
                UIUtils.ShutDownWindow(ref fileChooser);
            }
            else if (response == Utils.static_cast<int>(ResponseType.Accept))
			{
				string fullPath = fileChooser.Filename + "/exported_commands.xml";
				UIUtils.ShutDownWindow(ref fileChooser);
				UITabPage currentTabPage = GetCurrentTabPage();
				currentTabPage.GetGameConfig();

				GamesConfigLoader gamesLoader = MainApp.GetInstance().GetConfig().GetGameConfig();
                FileOperationResult fileOperationResult = gamesLoader.Export(fullPath, currentTabPage.GetGameConfig());
				
                if(!fileOperationResult.IsSuccess())
                {
					UIUtils.ShutDownWindowSafe(ref _windowPrompt);
                    _windowPrompt = new WindowPrompt(fileOperationResult.GetResult());
                    _windowPrompt.OnAcceptEvent += OnAlertAccept;
					_windowPrompt.SetCancelVisible(false);
					_windowPrompt.Show();
					MainApp.GetInstance().MoveWindowToMousePos(_windowPrompt);
				}
			}
		}

		private void OnAlertAccept()
		{
			UIUtils.ShutDownWindow(ref _windowPrompt);
		}

		protected void OnImportCommandsButtonPress(object sender, EventArgs e)
		{
			Gtk.FileChooserDialog fileChooser = new Gtk.FileChooserDialog
			("Choose files"
			, this
			, FileChooserAction.Open
			, "Select"
			, ResponseType.Accept
			, "Cancel"
			, ResponseType.Close);

			Gtk.FileFilter xmlFileFilter = new Gtk.FileFilter();
			xmlFileFilter.AddPattern("*.xml");
			fileChooser.AddFilter(xmlFileFilter);

			int response = fileChooser.Run();
            if (response == Utils.static_cast<int>(ResponseType.Close))
            {
                UIUtils.ShutDownWindow(ref fileChooser);
            }
            else if (response == Utils.static_cast<int>(ResponseType.Accept))
			{
				string fullPath = fileChooser.Filename;
				UIUtils.ShutDownWindow(ref fileChooser);

                GameConfigDescriptorLoader loader = new GameConfigDescriptorLoader(fullPath);
                FileOperationResult fileOperationResult = loader.Load();

                if (fileOperationResult.IsSuccess())
                {
                    GameConfigDB sourceConfigDB = loader.GetConfig();

					UITabPage currentTabPage = GetCurrentTabPage();
					GameConfigDB targetConfigDB = currentTabPage.GetGameConfig();

					foreach (GameConfigSectionDescriptor sectionDescriptor in sourceConfigDB.GetSections())
					{
						targetConfigDB.AddSection(sectionDescriptor);
						currentTabPage.AddNewSection(sectionDescriptor);
					}

					currentTabPage.RefreshCanvas();
				}
				else
				{
					UIUtils.ShutDownWindowSafe(ref _windowPrompt);
                    _windowPrompt = new WindowPrompt(fileOperationResult.GetResult());
                    _windowPrompt.OnAcceptEvent += OnAlertAccept;
					_windowPrompt.SetCancelVisible(false);
					_windowPrompt.Show();
					MainApp.GetInstance().MoveWindowToMousePos(_windowPrompt);
				}
			}
		}
	}
}
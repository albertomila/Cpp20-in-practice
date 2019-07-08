using System;
using Gtk;
using System.Drawing;
using System.Collections.Generic;
using System.Net;

namespace Comando
{
	public class MainApp : Singleton<MainApp>
	{
		private Config _config = null;
		private MainWindow _mainWindow = null;
		private WindowConfiguration _windowConfiguration = null;
		private WindowHostTargets _windowHostTargets = null;
		private HostsController _hostsController = null;
		private WindowPrompt _windowPrompt = null;
        private CommandsTable _availableCommands = null;
		private WindowCommandList _windowCommandList = null;

        public MainApp()
		{
			_config = new Config();
			_hostsController = new HostsController();
            _availableCommands = new CommandsTable();
            DraggingController.CreateInstance();
        }
        
        public CommandsTable GetCommands()
        {
            return _availableCommands;
        }

		public void Init()
        {
            Application.Init();
            _config.Load();
			_mainWindow = new MainWindow();
			_hostsController.Init();
            _hostsController.TryConnectAll();
        }

		public void Run()
		{
			_mainWindow.Show();

			while (_mainWindow.IsRunning())
			{
				while (Application.EventsPending())
				{
					Application.RunIteration(false);
				}

				_mainWindow.Uptade();
                _hostsController.Update();
                if(_windowHostTargets != null)
                {
                    _windowHostTargets.RefreshVisuals();
                }

				if (_windowCommandList != null)
				{
					_windowCommandList.Update();
				}
            }

			UIUtils.ShutDownWindow(ref _mainWindow);
			Application.Quit();
		}

		public Config GetConfig()
		{
			return _config;
		}

		public void OnMenuConfigurationButtonPress(object sender, EventArgs e)
		{
			UIUtils.ShutDownWindowSafe(ref _windowConfiguration);
			ApplicationConfig appConfig = _config.GetApplicationConfig();
			_windowConfiguration = new WindowConfiguration();
			_windowConfiguration.SetPort(appConfig._port.ToString());
			_windowConfiguration.SetService(appConfig._service);
			_windowConfiguration.SetTarget(appConfig._sendCommand);
			_windowConfiguration.SetTargetCommand(appConfig._sendConsoleCommand);
			_windowConfiguration.SetDefaultIP(appConfig._defaultHost);
            MoveWindowToWindowPos(_windowConfiguration);
            _windowConfiguration.Show();
		}

		public void OnWindowAcceptButtonPressed(object sender, EventArgs e)
		{
			ApplicationConfig appConfig = _config.GetApplicationConfig();
			appConfig._port = int.Parse(_windowConfiguration.GetPort());
			appConfig._service = _windowConfiguration.GetService();
			appConfig._sendCommand = _windowConfiguration.GetTarget();
			appConfig._sendConsoleCommand = _windowConfiguration.GetTargetCommand();
			appConfig._defaultHost = _windowConfiguration.GetDefaultIP();

            UIUtils.ShutDownWindow(ref _windowConfiguration);
		}

		public void OnButtonPressEvent(GameConfigButtonDescriptor commandDescriptor)
		{
			if (commandDescriptor._type == GameConfigButtonDescriptor.Etype.FixedArgument
			   || commandDescriptor._type == GameConfigButtonDescriptor.Etype.ExposedArgument)
			{
				ExecuteCommand(commandDescriptor._command, commandDescriptor._arguments);
			}
			else if (commandDescriptor._type == GameConfigButtonDescriptor.Etype.MultiCommand)
			{
				foreach (GameConfigCommandDescriptor command in commandDescriptor._commandList)
				{
                	ExecuteCommand(command._command, command._arguments);
				}
			}
		}

        public void ExecuteCommand(string command, string arguments)
        {
			if (_hostsController.IsAnyHostDisconnected())
			{
				_hostsController.TryConnectAll();
                OpenWindowAddTargetSafe();
			}

			ApplicationConfig appConfig = MainApp.GetInstance().GetConfig().GetApplicationConfig();
			ExecuteCommandAllTargets(appConfig._sendCommand, command, arguments);
        }

		public void ExecuteConsoleCommand(string commandWithArgs)
		{
			if (_hostsController.IsAnyHostDisconnected())
			{
				_hostsController.TryConnectAll();
                OpenWindowAddTargetSafe();
			}

			ApplicationConfig appConfig = MainApp.GetInstance().GetConfig().GetApplicationConfig();
			ExecuteCommandAllTargets(appConfig._sendConsoleCommand, commandWithArgs, string.Empty);
        }

		private void ExecuteCommandAllTargets(string targetCommand, string command, string arguments)
		{
			List<HostStatus> hosts = _hostsController.GetHosts();
			foreach (HostStatus host in hosts)
			{
				if (host._connectionStatus == HostStatus.EStatus.Connected)
				{
					ExecuteSingleCommandOnHost(host, targetCommand, command, arguments);
				}
				else
				{				
					_mainWindow.GetConsole().WriteOutput(host._host + ": sent failed");
				}
			}
		}

        private void ExecuteSingleCommandOnHost(HostStatus host, string targetCommand, string command, string arguments)
        {
            try
            {
                ApplicationConfig appConfig = MainApp.GetInstance().GetConfig().GetApplicationConfig();
                string message = "";
                string urlCommand = string.Empty;
                urlCommand += "http://";
                urlCommand += host._host;
                urlCommand += ":" + appConfig._port;
                urlCommand += "/" + appConfig._service;
                urlCommand += "/" + targetCommand;
                urlCommand += "?command=" + command;
				if (arguments.Length > 0)
				{
                	urlCommand += "&" + arguments;
				}

                WebRequest wrGETURL;
                wrGETURL = WebRequest.Create(urlCommand);

                System.IO.Stream objStream;
                objStream = wrGETURL.GetResponse().GetResponseStream();

                System.IO.StreamReader objReader = new System.IO.StreamReader(objStream);

                string sLine = "";

                while (sLine != null)
                {
                    sLine = objReader.ReadLine();
                    if (sLine != null)
                    {
                        message += sLine;
                    }
                }

                ProcessResponseMesssage(host, command, message);
            }
            catch (System.Exception ex)
            {
				_mainWindow.GetConsole().WriteOutput(host._host + ": sent failed, " + ex.Message);
				host._connectionStatus = HostStatus.EStatus.Disconnected;
				_hostsController.TryConnectHost(host);
            }
        }

        private void ProcessResponseMesssage(HostStatus host, string command, string message)
        {
			SimpleJSON.JSONNode jsonResponse = SimpleJSON.JSON.Parse(message);

            string output = string.Empty;
            string resultValue = jsonResponse["result"];

            if (resultValue != null && resultValue == "1")
            {
                output = host._host + ": sent succcess";

                string restultData = jsonResponse["data"];
                if (restultData != null)
                {
                    output += restultData;
                }
            }
            else
            {
                output = host._host + ": sent failed";
            }


            _mainWindow.GetConsole().WriteOutput(output);
        }


		public void OnOpenWindowAddTargetButtonPress()
		{
			OpenWindowAddTargetSafe();
		}

		public void OpenWindowAddTargetSafe()
		{
			if (_windowHostTargets != null)
            {
                UIUtils.ShutDownWindow(ref _windowHostTargets);
			}
			UIUtils.ShutDownWindowSafe(ref _windowHostTargets);
			_windowHostTargets = new WindowHostTargets(GetHostsController().GetHosts());

			MoveWindowToWindowPos(_windowHostTargets);
			_windowHostTargets.Show();
		}

		public void OnAddHostTargetsButtonPress(List<string> hostTargets)
        {
            UIUtils.ShutDownWindow(ref _windowHostTargets);
			_config.GetApplicationConfig()._hostTargets = hostTargets;
		}

		private Point GetWindowMousePos()
		{
			int outX = 0;
			int outY = 0;
			_mainWindow.GetPointer(out outX, out outY);
			return new Point(outX, outY);
		}

		public Point GetCanvasMousePos()
		{
			return _mainWindow.GetCurrentTabPage().GetCanvasMousePos();
		}

		public Point GetWindowPos()
		{
			int outX = 0;
			int outY = 0;
			_mainWindow.GetPosition(out outX, out outY);
			return new Point(outX, outY);
		}

        public void MoveWindowToMousePos(Gtk.Window window)
		{
			Point mousePos = GetWindowMousePos();
			window.Move(mousePos.X, mousePos.Y);
        }

        public void MoveWindowToWindowPos(Gtk.Window window)
        {
            Point windowPos = GetWindowPos();
            window.Move(windowPos.X, windowPos.Y);
        }

        public WidgetConsole GetConsole()
		{
			return _mainWindow.GetConsole();
		}

		public HostsController GetHostsController()
		{
			return _hostsController;
		}

		public WindowPrompt GetWindowPrompt()
		{
			return _windowPrompt;
		}

		public void OpenCommandPicker(WindowCommandList.OnCommandPicked onCommandPickedCallback)
		{
			if (_windowCommandList != null)
			{
				CloseCommandPicker();
			}
			UIUtils.ShutDownWindowSafe(ref _windowCommandList);
			_windowCommandList = new WindowCommandList();
			_windowCommandList.OnCommandPickedEvent += onCommandPickedCallback;
			_windowCommandList.Show();
			MainApp.GetInstance().MoveWindowToMousePos(_windowCommandList);
		}

		public void CloseCommandPicker()
		{
			UIUtils.ShutDownWindow(ref _windowCommandList);
		}
	}
}
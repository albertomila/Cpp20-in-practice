using System;
using System.Collections.Generic;
using System.Net;
using System.Net.NetworkInformation;
using System.Collections;

namespace Comando
{
	public class HostConnectionThread
	{
		public delegate void OnConnectionCallback(HostStatus host, string resultMessage);
		private HostStatus _host;
		private string _resultMessage;
		public event OnConnectionCallback OnConnectionDoneEvent = null;

		public HostConnectionThread(HostStatus host)
		{
			_host = host;
		}

		public string GetResultMessage()
		{
			return _resultMessage;
		}

		public void ExecuteThread()
		{
			_host._connectionStatus = HostStatus.EStatus.Connecting;
			bool pingSuccess = false;

			int timeout = 2;
			try
			{
				Ping ping = new Ping();
				PingReply pingReply = ping.Send(_host._host, timeout);
				pingSuccess = pingReply.Status == IPStatus.Success;
			}
			catch (System.Net.Sockets.SocketException /*e*/)
    		{
				_resultMessage = "Host ("+ _host._host + ") not available\n";
			    _host._connectionStatus = HostStatus.EStatus.Disconnected;
				OnConnectionDoneEvent?.Invoke(_host, _resultMessage);

				return;
			}
			catch (PingException /*e*/)
    		{
				_resultMessage = "Host ("+ _host._host + ") not available\n";
			    _host._connectionStatus = HostStatus.EStatus.Disconnected;
				OnConnectionDoneEvent?.Invoke(_host, _resultMessage);

				return;
			}

			if (pingSuccess)
			{
                ApplicationConfig appConfig = MainApp.GetInstance().GetConfig().GetApplicationConfig();
				string urlCommand = string.Empty;
				urlCommand += "http://";
				urlCommand += _host._host;
                urlCommand += ":" + appConfig._port;
                urlCommand += "/" + appConfig._service;

				WebRequest wrGETURL;
				wrGETURL = WebRequest.Create(urlCommand);

				WebResponse webResponse = null;
				try
				{
					_host._connectionStatus = HostStatus.EStatus.Connecting;
					webResponse = wrGETURL.GetResponse();

					System.IO.Stream objStream;
					objStream = webResponse.GetResponseStream();

					System.IO.StreamReader objReader = new System.IO.StreamReader(objStream);

					string sLine = "";
					while (sLine != null)
					{
						sLine = objReader.ReadLine();
						if (sLine != null)
						{
							_resultMessage += sLine;
						}
					}

                    CommandsTable commandsTable = MainApp.GetInstance().GetCommands();
                    SimpleJSON.JSONNode jsonResponse = SimpleJSON.JSON.Parse(_resultMessage);
                    SimpleJSON.JSONClass jsonObject = jsonResponse.AsObject;

                    foreach (KeyValuePair<string, SimpleJSON.JSONNode> commandPair in jsonObject)
                    {
                        string commandName = commandPair.Key;
                        string commandDescription = commandPair.Value;

                        commandsTable.AddCommand(commandName, commandDescription);
                    }

                    _host._connectionStatus = HostStatus.EStatus.Connected;

                    Messenger.Broadcast("OnCommandsSync");
					_resultMessage = "Connected to host: (" + _host._host + ")\n";
                }
				catch (System.Net.WebException /*ex*/)
				{
					_resultMessage = "Could not connect to host: (" + _host._host + "), open the game in this device to send commands\n";
                    _host._connectionStatus = HostStatus.EStatus.Disconnected;
				}
			}
			else
			{
				_resultMessage = "Could not connect to host: (" + _host._host + "), open the game in this device to send commands\n";
                _host._connectionStatus = HostStatus.EStatus.Disconnected;
			}

			OnConnectionDoneEvent?.Invoke(_host, _resultMessage);
		}
	}
}

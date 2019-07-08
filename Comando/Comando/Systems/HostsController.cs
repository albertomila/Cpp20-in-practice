using System;
using System.Collections.Generic;
using System.Threading;

namespace Comando
{
	public class HostsController
	{
		public delegate void OnConnectionAllDone();
		private List<HostStatus> _hosts = null;
		private ApplicationConfig _applicationConfig = null;
		private bool _isFirstAttempt = false;
		public event OnConnectionAllDone OnConnectionAllDoneEvent = null;
		private List<string> _pendingMessages = null;
		private Mutex _mutexPendingMessages = null;


		public HostsController()
		{
			_hosts = new List<HostStatus>();
			_pendingMessages = new List<string>();
			_mutexPendingMessages = new Mutex();
        }

		public void Init()
		{
			_applicationConfig = MainApp.GetInstance().GetConfig().GetApplicationConfig();

			foreach (string host in _applicationConfig._hostTargets)
			{
				AddHost(host);
			}
		}

		public bool IsAnyHostDisconnected()
		{
			foreach (HostStatus host in _hosts)
			{
				if (host._connectionStatus == HostStatus.EStatus.Disconnected)
				{
					return true;
				}
			}

			return false;
		}

		public void Update()
		{
			if (_pendingMessages.Count > 0)
			{
				_mutexPendingMessages.WaitOne();
				foreach (string pendingMessage in _pendingMessages)
				{
					MainApp.GetInstance().GetConsole().WriteOutput(pendingMessage);
				}
				_pendingMessages.Clear();
				_mutexPendingMessages.ReleaseMutex();
			}
		}

		public bool HasFirstConnected()
		{
			return _isFirstAttempt;
		}

		public List<HostStatus> GetHosts()
		{
			return _hosts;
		}

		public HostStatus AddHost(string host)
		{
			HostStatus newHost = new HostStatus();
			newHost._host = host;
			_hosts.Add(newHost);

			return newHost;
		}

		public void RemoveHost(HostStatus host)
		{
			_hosts.Remove(host);
		}

		public void TryConnectAll()
		{
			foreach (HostStatus host in _hosts)
			{
				if (host._connectionStatus == HostStatus.EStatus.Disconnected)
				{
					TryConnectHost(host);
				}
			}

            OnConnectionAllDoneEvent?.Invoke();

			_isFirstAttempt = true;
		}

		public void TryConnectHost(HostStatus host)
		{
			HostConnectionThread hostConnectionThread = new HostConnectionThread(host);
			hostConnectionThread.OnConnectionDoneEvent += RegisterConnectionMessage;

			Thread connectionThread = new Thread(hostConnectionThread.ExecuteThread);
			connectionThread.Start();
		}

		public void RegisterConnectionMessage(HostStatus host, string resultMessage)
		{
			_mutexPendingMessages.WaitOne();
			_pendingMessages.Add(resultMessage);
			_mutexPendingMessages.ReleaseMutex();
		}
	}
}

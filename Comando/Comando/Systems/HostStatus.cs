using System;
namespace Comando
{
	public class HostStatus
	{
		public enum EStatus
		{
			Disconnected,
			Connecting,
			Connected
		}

		public string _host = string.Empty;
		public EStatus _connectionStatus = EStatus.Disconnected;
	}
}

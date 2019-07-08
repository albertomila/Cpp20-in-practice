using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Comando
{
    class DraggingController : Singleton<DraggingController>
    {
        private UICommandElement _draggedElement = null;
        public delegate void OnDropCallback(UICommandElement uiCommandElement);
        public event OnDropCallback OnDropEvent = null;

        public void SetDraggingElement(UICommandElement draggedElement)
        {
            UICommandElement previousDraggedElement = _draggedElement;
            _draggedElement = draggedElement;
            if(previousDraggedElement != null && draggedElement == null)
            {
				OnDropEvent?.Invoke(previousDraggedElement);
            }
        }

		public void ClearEvents()
		{
			OnDropEvent = null;
		}

        public UICommandElement GetDraggedElement()
        {
            return _draggedElement;
        }

        public bool IsDragging()
        {
            return _draggedElement != null;
        }
    }
}

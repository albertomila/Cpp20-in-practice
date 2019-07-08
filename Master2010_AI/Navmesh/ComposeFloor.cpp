#include "stdAfx.h"
#include "ComposeFloor.h"

CComposeFloor::CComposeFloor(void)
{ 
	_bPointFollowAdded = false;
	_bCompletePath = false;
}

CComposeFloor::~CComposeFloor(void)
{
}


float CComposeFloor::Distance(Point2 p1, Point2 p2)
{
	return sqrt(pow((float)p2.X - (float)p1.X,2) + pow((float)p2.Y - (float)p1.Y,2));
}
void CComposeFloor::OurWindowProcedure(UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
{
	if(!_bCompletePath)
	{
		POINTS ptsBegin;

		_currentPoint.X = GET_X_LPARAM(parameter2);
		_currentPoint.Y = 768 - GET_Y_LPARAM(parameter2);
		if( _currentPoint.X < 300 || _currentPoint.Y < 0 || _currentPoint.Y > 768)
		{
			if( _currentPoint.X < 300) _currentPoint.X = 300;
			if( _currentPoint.Y < 0)  _currentPoint.Y = 0;
			if(_vListPoints.size() > 0)
			{
				if(_iIndexPointFollow==(_vListPoints.size()-1))
				{
					_vListPoints.pop_back();
					_bPointFollowAdded = false;
				}
			}
		}
		else
		{
			if(!_bPointFollowAdded)
			{
				_vListPoints.push_back(_currentPoint);
				_iIndexPointFollow = _vListPoints.size() - 1;
				_bPointFollowAdded = true;
			}
			else
			{
				_vListPoints[_iIndexPointFollow].X = _currentPoint.X;
				_vListPoints[_iIndexPointFollow].Y = _currentPoint.Y;
			}


			for(int i=0; i<_vListPoints.size()-1; i++)
			{
				Point2 p2;
				p2.X = _vListPoints[i].X;
				p2.Y = _vListPoints[i].Y;
				float fd = Distance(p2,_currentPoint);
				if(fd < 20)
				{
					_vListPoints[_iIndexPointFollow].X = p2.X;
					_vListPoints[_iIndexPointFollow].Y = p2.Y;
					_currentPoint.X = _vListPoints[0].X;
					_currentPoint.Y = _vListPoints[0].Y;

				}
			}

			switch(uint_Message)
		 {
			case WM_LBUTTONDOWN: 
				int iX = GET_X_LPARAM(parameter2);
				int iY = GET_Y_LPARAM(parameter2);
				ptsBegin = MAKEPOINTS(parameter2); 
				ptsBegin.y = (768 - ptsBegin.y);
				Point2 p;
				p.X = ptsBegin.x;
				p.Y = ptsBegin.y;

				for(int i=0; i<_vListPoints.size()-1; i++)
				{
					Point2 p2;
					p2.X = _vListPoints[i].X;
					p2.Y = _vListPoints[i].Y;
					float fd = Distance(p,p2);
					if(fd < 20)
					{
						_bCompletePath = true;
						_vListPoints.pop_back();
						break;
					}
				}
				if(!_bCompletePath)
				{
					_vListPoints[_iIndexPointFollow].X = p.X;
					_vListPoints[_iIndexPointFollow].Y = p.Y;
					_bPointFollowAdded = false;
				}
				break;
		 }
		}
	}
}
bool CComposeFloor::complete() const
{
	return _bCompletePath;
}
vector<Point2> CComposeFloor::getListPoints()
{
	return _vListPoints;
}
void CComposeFloor::SetListPoints(vector<Point2> vListPoints)
{
	_vListPoints = vListPoints;
}


vector<ITEM> CComposeFloor::GetObstaclesTypes(int iDefaultMap)
{
	vector<ITEM>		vElements;
	ITEM it;
	switch(iDefaultMap)
	{
		case 0:
			it.p = Point2(ChangeX(581),ChangeY(709));
			it.type = 0;
			vElements.push_back(it);

			it.p = Point2(ChangeX(711),ChangeY(531));
			it.type = 0;
			vElements.push_back(it);

			it.p = Point2(ChangeX(572),ChangeY(312));
			it.type = 0;
			vElements.push_back(it);

			it.p =Point2(ChangeX(954),ChangeY(658));
			it.type = 1;
			vElements.push_back(it);

			it.p =Point2(ChangeX(483),ChangeY(845));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(1284),ChangeY(338));
			it.type = 0;
			vElements.push_back(it);

			it.p =Point2(ChangeX(1244),ChangeY(827));
			it.type = 3;
			vElements.push_back(it);

			it.p =Point2(ChangeX(533),ChangeY(157));
			it.type = 2;
			vElements.push_back(it);
			break;
		case 1:

			it.p =Point2(ChangeX(527),ChangeY(738));
			it.type = 0;
			vElements.push_back(it);

			it.p =Point2(ChangeX(711),ChangeY(611));
			it.type = 1;
			vElements.push_back(it);

			it.p =Point2(ChangeX(879),ChangeY(483));
			it.type = 0;
			vElements.push_back(it);

			it.p =Point2(ChangeX(1092),ChangeY(603));
			it.type = 1;
			vElements.push_back(it);

			it.p =Point2(ChangeX(1263),ChangeY(741));
			it.type = 0;
			vElements.push_back(it);

			it.p =Point2(ChangeX(605),ChangeY(392));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(714),ChangeY(306));
			it.type = 3;
			vElements.push_back(it);

			it.p =Point2(ChangeX(900),ChangeY(253));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(1078),ChangeY(343));
			it.type = 3;
			vElements.push_back(it);

			it.p =Point2(ChangeX(1242),ChangeY(449));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(546),ChangeY(183));
			it.type = 3;
			vElements.push_back(it);

			it.p =Point2(ChangeX(1303),ChangeY(182));
			it.type = 2;
			vElements.push_back(it);
			break;
		case 2:
			
			it.p =Point2(ChangeX(480),ChangeY(876));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(380),ChangeY(821));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(455),ChangeY(712));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(568),ChangeY(688));
			it.type = 2;
			vElements.push_back(it);

			it.p =Point2(ChangeX(538),ChangeY(190));
			it.type = 0;
			vElements.push_back(it);

			it.p =Point2(ChangeX(726),ChangeY(189));
			it.type = 1;
			vElements.push_back(it);
			break;
	}
	return vElements;
}
vector<obstacle> CComposeFloor::GetObstacles(int iDefaultMap)
{
	vector<obstacle> obstacles;
	obstacle ob;


	switch(iDefaultMap)
	{
		case 0:
			ob.push_back(Point2(ChangeX(581),ChangeY(709)));
			ob.push_back(Point2(ChangeX(741),ChangeY(709)));
			ob.push_back(Point2(ChangeX(741),ChangeY(793)));
			ob.push_back(Point2(ChangeX(581),ChangeY(793)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(711),ChangeY(531)));
			ob.push_back(Point2(ChangeX(871),ChangeY(531)));
			ob.push_back(Point2(ChangeX(871),ChangeY(615)));
			ob.push_back(Point2(ChangeX(711),ChangeY(615)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(572),ChangeY(312)));
			ob.push_back(Point2(ChangeX(732),ChangeY(312)));
			ob.push_back(Point2(ChangeX(732),ChangeY(396)));
			ob.push_back(Point2(ChangeX(572),ChangeY(396)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(954),ChangeY(658)));
			ob.push_back(Point2(ChangeX(1082),ChangeY(658)));
			ob.push_back(Point2(ChangeX(1082),ChangeY(758)));
			ob.push_back(Point2(ChangeX(954),ChangeY(758)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(483),ChangeY(845)));
			ob.push_back(Point2(ChangeX(547),ChangeY(845)));
			ob.push_back(Point2(ChangeX(547),ChangeY(925)));
			ob.push_back(Point2(ChangeX(483),ChangeY(925)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(1284),ChangeY(338)));
			ob.push_back(Point2(ChangeX(1444),ChangeY(338)));
			ob.push_back(Point2(ChangeX(1444),ChangeY(422)));
			ob.push_back(Point2(ChangeX(1284),ChangeY(422)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(1244),ChangeY(827)));
			ob.push_back(Point2(ChangeX(1308),ChangeY(827)));
			ob.push_back(Point2(ChangeX(1308),ChangeY(907)));
			ob.push_back(Point2(ChangeX(1244),ChangeY(907)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(533),ChangeY(157)));
			ob.push_back(Point2(ChangeX(597),ChangeY(157)));
			ob.push_back(Point2(ChangeX(597),ChangeY(237)));
			ob.push_back(Point2(ChangeX(533),ChangeY(237)));
			obstacles.push_back(ob);
			ob.clear();
		break;
		case 1:
			ob.push_back(Point2(ChangeX(527),ChangeY(738)));
			ob.push_back(Point2(ChangeX(687),ChangeY(738)));
			ob.push_back(Point2(ChangeX(687),ChangeY(822)));
			ob.push_back(Point2(ChangeX(527),ChangeY(822)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(711),ChangeY(611)));
			ob.push_back(Point2(ChangeX(839),ChangeY(611)));
			ob.push_back(Point2(ChangeX(839),ChangeY(711)));
			ob.push_back(Point2(ChangeX(711),ChangeY(711)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(879),ChangeY(483)));
			ob.push_back(Point2(ChangeX(1039),ChangeY(483)));
			ob.push_back(Point2(ChangeX(1039),ChangeY(567)));
			ob.push_back(Point2(ChangeX(879),ChangeY(567)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(1092),ChangeY(603)));
			ob.push_back(Point2(ChangeX(1220),ChangeY(603)));
			ob.push_back(Point2(ChangeX(1220),ChangeY(703)));
			ob.push_back(Point2(ChangeX(1092),ChangeY(703)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(1263),ChangeY(741)));
			ob.push_back(Point2(ChangeX(1423),ChangeY(741)));
			ob.push_back(Point2(ChangeX(1423),ChangeY(825)));
			ob.push_back(Point2(ChangeX(1263),ChangeY(825)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(605),ChangeY(392)));
			ob.push_back(Point2(ChangeX(669),ChangeY(392)));
			ob.push_back(Point2(ChangeX(669),ChangeY(472)));
			ob.push_back(Point2(ChangeX(605),ChangeY(472)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(714),ChangeY(306)));
			ob.push_back(Point2(ChangeX(778),ChangeY(306)));
			ob.push_back(Point2(ChangeX(778),ChangeY(386)));
			ob.push_back(Point2(ChangeX(714),ChangeY(386)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(900),ChangeY(253)));
			ob.push_back(Point2(ChangeX(964),ChangeY(253)));
			ob.push_back(Point2(ChangeX(964),ChangeY(333)));
			ob.push_back(Point2(ChangeX(900),ChangeY(333)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(1078),ChangeY(343)));
			ob.push_back(Point2(ChangeX(1142),ChangeY(343)));
			ob.push_back(Point2(ChangeX(1142),ChangeY(423)));
			ob.push_back(Point2(ChangeX(1078),ChangeY(423)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(1242),ChangeY(449)));
			ob.push_back(Point2(ChangeX(1306),ChangeY(449)));
			ob.push_back(Point2(ChangeX(1306),ChangeY(529)));
			ob.push_back(Point2(ChangeX(1242),ChangeY(529)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(546),ChangeY(183)));
			ob.push_back(Point2(ChangeX(610),ChangeY(183)));
			ob.push_back(Point2(ChangeX(610),ChangeY(263)));
			ob.push_back(Point2(ChangeX(546),ChangeY(263)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(1303),ChangeY(182)));
			ob.push_back(Point2(ChangeX(1367),ChangeY(182)));
			ob.push_back(Point2(ChangeX(1367),ChangeY(262)));
			ob.push_back(Point2(ChangeX(1303),ChangeY(262)));
			obstacles.push_back(ob);
			ob.clear();
			break;
		case 2:
			ob.push_back(Point2(ChangeX(480),ChangeY(876)));
			ob.push_back(Point2(ChangeX(544),ChangeY(876)));
			ob.push_back(Point2(ChangeX(544),ChangeY(956)));
			ob.push_back(Point2(ChangeX(480),ChangeY(956)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(380),ChangeY(821)));
			ob.push_back(Point2(ChangeX(444),ChangeY(821)));
			ob.push_back(Point2(ChangeX(444),ChangeY(901)));
			ob.push_back(Point2(ChangeX(380),ChangeY(901)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(455),ChangeY(712)));
			ob.push_back(Point2(ChangeX(519),ChangeY(712)));
			ob.push_back(Point2(ChangeX(519),ChangeY(792)));
			ob.push_back(Point2(ChangeX(455),ChangeY(792)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(568),ChangeY(688)));
			ob.push_back(Point2(ChangeX(632),ChangeY(688)));
			ob.push_back(Point2(ChangeX(632),ChangeY(768)));
			ob.push_back(Point2(ChangeX(568),ChangeY(768)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(538),ChangeY(190)));
			ob.push_back(Point2(ChangeX(698),ChangeY(190)));
			ob.push_back(Point2(ChangeX(698),ChangeY(274)));
			ob.push_back(Point2(ChangeX(538),ChangeY(274)));
			obstacles.push_back(ob);
			ob.clear();
			ob.push_back(Point2(ChangeX(726),ChangeY(189)));
			ob.push_back(Point2(ChangeX(854),ChangeY(189)));
			ob.push_back(Point2(ChangeX(854),ChangeY(289)));
			ob.push_back(Point2(ChangeX(726),ChangeY(289)));
			obstacles.push_back(ob);
			ob.clear();

			break;
	}

	return obstacles;
}

int CComposeFloor::ChangeX(int iValue)
{
	return (int)(0.719 * (float)iValue);
}
int CComposeFloor::ChangeY(int iValue)
{
	return (int)(0.7314 * (float)iValue);
}
void CComposeFloor::SetDefaultMap(int iDefaultMap)
{
	/*string s ="";
	for(int i=0; i<_vListPoints.size(); i++)
	{
		s+= "_vListPoints.push_back(Point2(ChangeX(";
		std::stringstream out;
		out << _vListPoints[i].X;
		s += out.str();

		s+= "),ChangeY(";
		std::stringstream out2;
		out2 << _vListPoints[i].Y;
		s += out2.str();
		s+= "));";
	}*/
	_vListPoints.clear();
	switch(iDefaultMap)
	{
		case 0:
			_vListPoints.push_back(Point2(ChangeX(431),ChangeY(973)));
			_vListPoints.push_back(Point2(ChangeX(387),ChangeY(956)));
			_vListPoints.push_back(Point2(ChangeX(370),ChangeY(904)));
			_vListPoints.push_back(Point2(ChangeX(391),ChangeY(812)));
			_vListPoints.push_back(Point2(ChangeX(449),ChangeY(696)));
			_vListPoints.push_back(Point2(ChangeX(512),ChangeY(623)));
			_vListPoints.push_back(Point2(ChangeX(541),ChangeY(570)));
			_vListPoints.push_back(Point2(ChangeX(521),ChangeY(474)));
			_vListPoints.push_back(Point2(ChangeX(447),ChangeY(390)));
			_vListPoints.push_back(Point2(ChangeX(397),ChangeY(324)));
			_vListPoints.push_back(Point2(ChangeX(366),ChangeY(278)));
			_vListPoints.push_back(Point2(ChangeX(347),ChangeY(195)));
			_vListPoints.push_back(Point2(ChangeX(390),ChangeY(88)));
			_vListPoints.push_back(Point2(ChangeX(703),ChangeY(42)));
			_vListPoints.push_back(Point2(ChangeX(762),ChangeY(105)));
			_vListPoints.push_back(Point2(ChangeX(828),ChangeY(203)));
			_vListPoints.push_back(Point2(ChangeX(859),ChangeY(312)));
			_vListPoints.push_back(Point2(ChangeX(915),ChangeY(388)));
			_vListPoints.push_back(Point2(ChangeX(980),ChangeY(439)));
			_vListPoints.push_back(Point2(ChangeX(1068),ChangeY(450)));
			_vListPoints.push_back(Point2(ChangeX(1153),ChangeY(410)));
			_vListPoints.push_back(Point2(ChangeX(1194),ChangeY(361)));
			_vListPoints.push_back(Point2(ChangeX(1272),ChangeY(270)));
			_vListPoints.push_back(Point2(ChangeX(1330),ChangeY(184)));
			_vListPoints.push_back(Point2(ChangeX(1394),ChangeY(104)));
			_vListPoints.push_back(Point2(ChangeX(1498),ChangeY(70)));
			_vListPoints.push_back(Point2(ChangeX(1559),ChangeY(91)));
			_vListPoints.push_back(Point2(ChangeX(1593),ChangeY(152)));
			_vListPoints.push_back(Point2(ChangeX(1598),ChangeY(260)));
			_vListPoints.push_back(Point2(ChangeX(1576),ChangeY(357)));
			_vListPoints.push_back(Point2(ChangeX(1552),ChangeY(423)));
			_vListPoints.push_back(Point2(ChangeX(1494),ChangeY(488)));
			_vListPoints.push_back(Point2(ChangeX(1337),ChangeY(566)));
			_vListPoints.push_back(Point2(ChangeX(1304),ChangeY(608)));
			_vListPoints.push_back(Point2(ChangeX(1319),ChangeY(697)));
			_vListPoints.push_back(Point2(ChangeX(1415),ChangeY(765)));
			_vListPoints.push_back(Point2(ChangeX(1512),ChangeY(863)));
			_vListPoints.push_back(Point2(ChangeX(1534),ChangeY(920)));
			_vListPoints.push_back(Point2(ChangeX(1530),ChangeY(979)));
			_vListPoints.push_back(Point2(ChangeX(1437),ChangeY(1025)));
			_vListPoints.push_back(Point2(ChangeX(1272),ChangeY(1032)));
			_vListPoints.push_back(Point2(ChangeX(1164),ChangeY(975)));
			_vListPoints.push_back(Point2(ChangeX(1055),ChangeY(874)));
			_vListPoints.push_back(Point2(ChangeX(894),ChangeY(837)));
			_vListPoints.push_back(Point2(ChangeX(721),ChangeY(869)));
			_vListPoints.push_back(Point2(ChangeX(657),ChangeY(934)));
			_vListPoints.push_back(Point2(ChangeX(635),ChangeY(978)));
			break;
		case 1:
			_vListPoints.push_back(Point2(ChangeX(491),ChangeY(975)));
			_vListPoints.push_back(Point2(ChangeX(443),ChangeY(973)));
			_vListPoints.push_back(Point2(ChangeX(376),ChangeY(909)));
			_vListPoints.push_back(Point2(ChangeX(359),ChangeY(801)));
			_vListPoints.push_back(Point2(ChangeX(359),ChangeY(715)));
			_vListPoints.push_back(Point2(ChangeX(357),ChangeY(606)));
			_vListPoints.push_back(Point2(ChangeX(350),ChangeY(511)));
			_vListPoints.push_back(Point2(ChangeX(339),ChangeY(393)));
			_vListPoints.push_back(Point2(ChangeX(345),ChangeY(297)));
			_vListPoints.push_back(Point2(ChangeX(410),ChangeY(164)));
			_vListPoints.push_back(Point2(ChangeX(570),ChangeY(76)));
			_vListPoints.push_back(Point2(ChangeX(802),ChangeY(49)));
			_vListPoints.push_back(Point2(ChangeX(978),ChangeY(53)));
			_vListPoints.push_back(Point2(ChangeX(1177),ChangeY(53)));
			_vListPoints.push_back(Point2(ChangeX(1402),ChangeY(67)));
			_vListPoints.push_back(Point2(ChangeX(1521),ChangeY(127)));
			_vListPoints.push_back(Point2(ChangeX(1627),ChangeY(243)));
			_vListPoints.push_back(Point2(ChangeX(1638),ChangeY(328)));
			_vListPoints.push_back(Point2(ChangeX(1634),ChangeY(459)));
			_vListPoints.push_back(Point2(ChangeX(1630),ChangeY(617)));
			_vListPoints.push_back(Point2(ChangeX(1625),ChangeY(749)));
			_vListPoints.push_back(Point2(ChangeX(1608),ChangeY(858)));
			_vListPoints.push_back(Point2(ChangeX(1587),ChangeY(922)));
			_vListPoints.push_back(Point2(ChangeX(1533),ChangeY(961)));
			_vListPoints.push_back(Point2(ChangeX(1431),ChangeY(968)));
			_vListPoints.push_back(Point2(ChangeX(1294),ChangeY(974)));
			_vListPoints.push_back(Point2(ChangeX(1207),ChangeY(969)));
			_vListPoints.push_back(Point2(ChangeX(1043),ChangeY(970)));
			_vListPoints.push_back(Point2(ChangeX(894),ChangeY(971)));
			_vListPoints.push_back(Point2(ChangeX(680),ChangeY(985)));
			break;
		case 2:
			_vListPoints.push_back(Point2(ChangeX(1625),ChangeY(1016)));
			_vListPoints.push_back(Point2(ChangeX(1481),ChangeY(1009)));
			_vListPoints.push_back(Point2(ChangeX(1073),ChangeY(1010)));
			_vListPoints.push_back(Point2(ChangeX(793),ChangeY(981)));
			_vListPoints.push_back(Point2(ChangeX(532),ChangeY(987)));
			_vListPoints.push_back(Point2(ChangeX(422),ChangeY(963)));
			_vListPoints.push_back(Point2(ChangeX(364),ChangeY(910)));
			_vListPoints.push_back(Point2(ChangeX(320),ChangeY(819)));
			_vListPoints.push_back(Point2(ChangeX(337),ChangeY(732)));
			_vListPoints.push_back(Point2(ChangeX(498),ChangeY(665)));
			_vListPoints.push_back(Point2(ChangeX(693),ChangeY(670)));
			_vListPoints.push_back(Point2(ChangeX(862),ChangeY(669)));
			_vListPoints.push_back(Point2(ChangeX(1070),ChangeY(662)));
			_vListPoints.push_back(Point2(ChangeX(1199),ChangeY(644)));
			_vListPoints.push_back(Point2(ChangeX(1267),ChangeY(611)));
			_vListPoints.push_back(Point2(ChangeX(1294),ChangeY(578)));
			_vListPoints.push_back(Point2(ChangeX(1303),ChangeY(504)));
			_vListPoints.push_back(Point2(ChangeX(1278),ChangeY(457)));
			_vListPoints.push_back(Point2(ChangeX(1112),ChangeY(418)));
			_vListPoints.push_back(Point2(ChangeX(884),ChangeY(434)));
			_vListPoints.push_back(Point2(ChangeX(660),ChangeY(438)));
			_vListPoints.push_back(Point2(ChangeX(512),ChangeY(415)));
			_vListPoints.push_back(Point2(ChangeX(413),ChangeY(374)));
			_vListPoints.push_back(Point2(ChangeX(368),ChangeY(300)));
			_vListPoints.push_back(Point2(ChangeX(341),ChangeY(156)));
			_vListPoints.push_back(Point2(ChangeX(393),ChangeY(95)));
			_vListPoints.push_back(Point2(ChangeX(545),ChangeY(61)));
			_vListPoints.push_back(Point2(ChangeX(780),ChangeY(51)));
			_vListPoints.push_back(Point2(ChangeX(1113),ChangeY(60)));
			_vListPoints.push_back(Point2(ChangeX(1320),ChangeY(83)));
			_vListPoints.push_back(Point2(ChangeX(1472),ChangeY(179)));
			_vListPoints.push_back(Point2(ChangeX(1541),ChangeY(301)));
			_vListPoints.push_back(Point2(ChangeX(1582),ChangeY(443)));
			_vListPoints.push_back(Point2(ChangeX(1583),ChangeY(553)));
			_vListPoints.push_back(Point2(ChangeX(1572),ChangeY(652)));
			_vListPoints.push_back(Point2(ChangeX(1384),ChangeY(718)));
			_vListPoints.push_back(Point2(ChangeX(1243),ChangeY(745)));
			_vListPoints.push_back(Point2(ChangeX(986),ChangeY(764)));
			_vListPoints.push_back(Point2(ChangeX(728),ChangeY(774)));
			_vListPoints.push_back(Point2(ChangeX(543),ChangeY(794)));
			_vListPoints.push_back(Point2(ChangeX(526),ChangeY(827)));
			_vListPoints.push_back(Point2(ChangeX(613),ChangeY(866)));
			_vListPoints.push_back(Point2(ChangeX(875),ChangeY(872)));
			_vListPoints.push_back(Point2(ChangeX(1208),ChangeY(865)));
			_vListPoints.push_back(Point2(ChangeX(1393),ChangeY(867)));
			_vListPoints.push_back(Point2(ChangeX(1541),ChangeY(877)));

			break;
	}
}


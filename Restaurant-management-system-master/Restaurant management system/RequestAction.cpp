#include "RequestAction.h"
#include "Ot.h"
#include "Ovn.h"
#include "OVC.h"
#include "OVG.h"
#include "ODG.h"
#include "ODN.h"
#include "COMBOorder.h"
string RequestAction::orderTypeStr()
{
	switch (type) {
	case ODG:
		return "ODG";
	case ODN:
		return "ODN";
	case OT:
		return "OT";
	case OVN:
		return "OVN";
	case OVC:
		return "OVC";
	case OVG:
		return "OVG";
	case COMBO:
		return "COMBO";
	}
}

void RequestAction::Act(Restaurant* res)
{
	Order* ord = nullptr;
	switch (type) {
	case ODG:
		ord = new Odg(OrderID, size, price, seats, duration, shareable);
		ord->setRequestTime(GetTime());
		res->add_odg(ord);
		ord->setRequestTime(this->time);
		break;
	case ODN:
		ord = new Odn(OrderID, size, price, seats, duration, shareable);
		ord->setRequestTime(GetTime());
		res->add_odn(ord);
		ord->setRequestTime(this->time);
		break;
	case OT:
		ord = new Ot(OrderID, size, price);
		ord->setRequestTime(GetTime());
		res->add_ot(ord);
		ord->setRequestTime(this->time);
		break;
	case OVN:
		ord = new Ovn(OrderID, size, price, distance);
		ord->setRequestTime(GetTime());
		res->add_ovn(ord);
		ord->setRequestTime(this->time);
		break;
	case OVC:
		ord = new Ovc(OrderID, size, price, distance);
		ord->setRequestTime(GetTime());
		res->add_ovc(ord);
		ord->setRequestTime(this->time);
		break;
	case OVG:
		ord = new Ovg(OrderID, size, price, distance, 0.0); // initixxxalize priority explicitly
		ord->setRequestTime(GetTime());
		res->add_ovg(ord, ord->GetPriority());
		ord->setRequestTime(this->time);
		break;
	case COMBO:
		ord = new COMBOorder(OrderID, size, distance);
		ord->setRequestTime(GetTime());
		res->add_combo(ord);
		ord->setRequestTime(this->time);
		break;
	}
}

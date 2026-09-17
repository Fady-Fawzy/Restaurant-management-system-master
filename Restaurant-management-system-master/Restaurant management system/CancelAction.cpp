#include "CancelAction.h"
void CancelAction::Act(Restaurant* res)
{
	res->CancelOVC(OrderID);
	
}
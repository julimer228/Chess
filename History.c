#include "History.h"

bool IsOnTheChessboard(Square* boardsquare)
{
	if (boardsquare->column >= 0 && boardsquare->column < 8 && boardsquare->row < 8 && boardsquare->row >= 0)
		return true;
	return false;
}

bool AddAnElement(Square *from, Square *to, HistoryElement* pHead)
{

}

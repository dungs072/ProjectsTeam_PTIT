#include "Table.h"
void Table::ShowMessageClear(wxGrid* grid)
{
	wxMessageDialog* dialog = new wxMessageDialog(NULL,
		wxT("Are you sure to clear?"), wxT("Warning"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	if (grid->IsSelection() && dialog->ShowModal() == wxID_YES)
	{
		DeleteSelectedRows();
	}
}
void Table::DeleteSelectedRows() {}

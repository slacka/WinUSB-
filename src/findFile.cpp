///File : findFile.cpp
//------------------------------------------------------------------------------
/*
    This file is part of WoeUSB.

    WoeUSB is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WoeUSB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WoeUSB.  If not, see <http://www.gnu.org/licenses/>.
*/
//------------------------------------------------------------------------------
#include "findFile.hpp"
#include <wx/version.h> 
//------------------------------------------------------------------------------

wxString findFile(const wxString &str)
{
    wxString testPath;

    testPath = wxGetCwd() + _T("/") + str;
    if(wxFileExists(testPath) || wxDirExists(testPath)) // Si c'est dans le dossier ./
    {
        return testPath;
    }

    testPath = _T("../") + str;
    if(wxFileExists(testPath) || wxDirExists(testPath)) // Si c'est dans le dossier ../
    {
        return testPath;
    }

    #if (defined(__UNIX__) && wxCHECK_VERSION(3, 0, 0))
    testPath = wxString(wxStandardPaths::Get().GetInstallPrefix() + _T("/share/") + _T(PACKAGE) + _T("/") + str);
    if(wxFileExists(testPath) || wxDirExists(testPath)) // Si c'est dans le dossier /usr/.../share/nomprog
    {
        return testPath;
    }
    //FIXME: remove when 2.8 depreciated 
    #elif (defined(__UNIX__) && wxCHECK_VERSION(2, 8, 0))
    testPath = wxString(wxStandardPaths().GetInstallPrefix() + _T("/share/") + _T(PACKAGE) + _T("/") + str);
    {
        return testPath;
    }
    #endif // defined(__UNIX__)

    #if wxCHECK_VERSION(3, 0, 0)
    testPath = wxString(wxStandardPaths::Get().GetDataDir() + _T("/") + str);
    //FIXME: remove when 2.8 depreciated 
    #else
    testPath = wxString(wxStandardPaths().GetDataDir() + _T("/") + str);
    #endif //wx2 legacy
    if(wxFileExists(testPath) || wxDirExists(testPath)) // Si c'est dans le dossier /usr/.../share/nomPaquet
    {
        return testPath;
    }

    // Si non
    wxMessageBox(_("File not Found : ") + str, _("Error"), wxICON_ERROR);
    return _T("");
}

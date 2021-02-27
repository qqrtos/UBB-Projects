#include "UI.h"
#include <Windows.h>
#include "CSVPlayList.h"
#include "RepositoryExceptions.h"

#include "UndoRedoController.h"

using namespace std;

int main()
{
	system("color f4");
	
	{
		/// Undo/Redo
		Repository testRepository{ "testSongs.txt" };
		UndoRedoController undoRedoController{ testRepository };
		FilePlaylist* playlist = new CSVPlaylist{};
		//Service(const Repository& r, FilePlaylist* p, SongValidator v, UndoRedoController& undoRedoController)
		Service testService(testRepository, playlist, SongValidator{}, undoRedoController);
		//Song(const std::string& artist, const std::string& title, const Duration& duration, const std::string& source);
		testService.addSongToRepository("Parquet Courts", "Wide Awake!", 3, 40, "youtube");
		testService.addSongToRepository("Death Grips", "The Powers that B", 4, 20, "spotify");
		testService.addSongToRepository("Kendrick Lamar", "The Blacker the Berry", 3, 40, "deezer");

		undoRedoController.undo();

		testRepository.removeSong(Song{ "Death Grips", "The Powers that B",Duration{4,20},"spotify" });

		undoRedoController.redo();

		for (auto song : testRepository.getSongs()) {
			std::cout << song << "\n";
		}

		delete playlist;
	}
	
	try
	{
		Repository repo("Songs.txt");
		UndoRedoController undoredo{ repo };
		FilePlaylist* p = new CSVPlaylist{};
		Service serv(repo, p, SongValidator{}, undoredo);
		UI ui(serv);
		ui.run();
		delete p;
	}
	catch (FileException&)
	{
		cout << "Repository file could not be opened! The application will terminate." << endl;
		return 1;
	}

	return 0;
}
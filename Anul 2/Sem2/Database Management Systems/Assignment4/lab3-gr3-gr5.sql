use [et-music]
go


CREATE OR ALTER PROCEDURE _Log
	@message nvarchar(200)
AS
BEGIN  
	PRINT(@message);
	INSERT INTO Logger(Message) VALUES (@message);
END
Go


CREATE OR ALTER PROCEDURE ClearTables
AS
BEGIN
	DELETE from SongsPlaylists
	DELETE from Songs
	DELETE from Playlists
	EXEC _Log 'Cleared the tables Songs, Playlists, SongsPlaylists'
END
GO


CREATE or ALTER PROCEDURE InsertRollbackIfFailed_grade3
AS
BEGIN TRY
	BEGIN TRAN
		exec _Log 'Inserting song'
		insert into Songs values(10, 'ree', 123, 1)

		exec _Log 'Inserting playlist'
		insert into Playlists values(10, 'reep', '2020-10-10')

		exec _Log 'Inserting relationship between Song and Playlist'
		insert into SongsPlaylists values(10, 10)

		exec _Log 'Inserting relationship between Song and Playlist'
		insert into SongsPlaylists values(10, 25)

		exec _Log 'Committing transaction'
	COMMIT TRAN
END TRY
BEGIN CATCH
	exec _Log 'Something went wrong! Rolling back transaction.'
	ROLLBACK TRAN
END CATCH
GO

EXEC InsertRollbackIfFailed_grade3
EXEC ClearTables

SELECT * from Songs
SELECT * from Playlists
SELECT * from SongsPlaylists



CREATE or ALTER PROCEDURE InsertRollbackIfFailed_grade5
AS
BEGIN TRAN _Tran
BEGIN TRY
	exec _Log 'Inserting song'
	insert into Songs values(10, 'ree', 123, 1)
	exec _Log 'Reached a save point'
	SAVE TRAN DataInsert

	exec _Log 'Inserting playlist'
	insert into Playlists values(10, 'reep', '2020-10-10')
	exec _Log 'Reached a save point'
	SAVE TRAN DataInsert

	exec _Log 'Inserting relationship between Song and Playlist'
	insert into SongsPlaylists values(10, 15)
	exec _Log 'Committing transaction'
	COMMIT TRAN _Tran
END TRY
BEGIN CATCH
	exec _Log 'Something went wrong! Rolling back transaction to the last save point.'
	ROLLBACK TRAN DataInsert
	COMMIT TRAN _Tran
END CATCH
GO

EXEC InsertRollbackIfFailed_grade5
EXEC ClearTables

SELECT * from Songs
SELECT * from Playlists
SELECT * from SongsPlaylists

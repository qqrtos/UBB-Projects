use [ET-Music]

-- Test tables: --
/*
 * ReleaseLabels
 * Albums
 * SongsArtists
*/


-- Views --
CREATE OR ALTER VIEW OneTableView AS
SELECT * from Songs

CREATE OR ALTER VIEW TwoTablesView AS
SELECT Artists.Name, Albums.Title FROM Albums
INNER JOIN Artists ON Artists.Id = Albums.ArtistId

CREATE OR ALTER VIEW TwoTablesGroupByView AS
SELECT count(*) as Count, Songs.IsInTop as InTop, Albums.Id as AlbumId from Songs
INNER JOIN Albums ON Albums.Id = Songs.AlbumId
GROUP BY Albums.Id, Songs.IsInTop
HAVING Songs.IsInTop = 1

CREATE OR ALTER PROCEDURE DeleteAll @tableName varchar(50)
as
	--delete from (select Name from Tables where name like '%'+@tableName+'%')
	exec('delete from ' + @tableName)
go

CREATE OR ALTER PROCEDURE InsertElements @tableName varchar(64), @nrOfRows int
AS
	if @nrOfRows < 1
	begin
		RAISERROR('Invalid number of rows.', 16, 1)
	end

	declare @artistId int
	declare @songId int
	declare @albumId int
	declare @date datetime

	declare @i int
	set @i = 0
	while @i < @nrOfRows
	begin
		if @tableName = 'ReleaseLabels'
		begin
			insert into ReleaseLabels values (@i, convert(varchar(3), @i), @i)
		end

		if @tableName = 'Albums'
		begin
			insert into Artists (Id, Name) values (@i, 'testname')
			select @artistId = Id from Artists where Id = @i

			insert into Albums (Id, Title, NumberOfSongs, Length, ArtistId, ReleaseDate)
			values (@i, 'testtitle', @i, @i, @artistId, '2000-01-01')
		end

		if @tableName = 'SongsArtists'
		begin
			--insert into Artists (Id, Name, DateOfBirth, BirthPlace) values (@i, convert(varchar(5), @i), '2000-03-03', '2000-03-03')
			--select @artistId = Id from Artists where Id = @i
			select @artistId = Id from Artists where Name = 'testname'

			--insert into Albums (Id, Title, NumberOfSongs, Length, Artwork, ReleaseLabelId, ArtistId, ReleaseDate) 
			--values (@i, 'testtitle', 2, 2, NULL, 1, (select Id from Artists where Id = @artistId), '2000-03-03')
			--select @albumId = Id from Albums where Id = @i
			select @albumId = Id from Albums where Title = 'testtitle'

			insert into Songs (Id, Title, AlbumId)
			values (@i, 'testtitle', @albumId)
			select @songId = Id from Songs where Id = @i

			insert into SongsArtists values (@songId, @artistId)
		end

		set @i = @i + 1
	end
GO

CREATE OR ALTER PROCEDURE DeleteRows @tableName varchar(64), @nrOfRows int
as
	if @nrOfRows < 1
	begin
		RAISERROR('Invalid number of rows.', 16, 1)
	end

	declare @lastRow int
	if @tableName = 'ReleaseLabels'
	begin
		set @lastRow = (select max(id) from ReleaseLabels) - @nrOfRows
		delete from ReleaseLabels where Id > @lastRow
	end

	if @tableName = 'Albums'
	begin
		set @lastRow = (select max(id) from Albums) - @nrOfRows
		delete from Songs where AlbumId > @lastRow
		delete from Albums where Id > @lastRow
	end
	
	if @tableName = 'SongsArtists'
	begin
		if @nrOfRows > (select count(*) from SongsArtists)
		begin
			RAISERROR('Invalid number of rows.', 16, 1)
		end
		delete TOP(@nrOfRows) from SongsArtists 
	end
go

CREATE OR ALTER PROCEDURE SelectView @viewName varchar(50)
as
	if @viewName = 'OneTableView'
	begin
		select * from OneTableView
	end

	if @viewName = 'TwoTablesView'
	begin
		select * from TwoTablesView
	end

	if @viewName = 'TwoTablesGroupByView'
	begin
		select * from TwoTablesGroupByView
	end
go

CREATE OR ALTER PROCEDURE LogTest @testedEntityName varchar(50), @operation varchar(50), @start datetime, @end datetime
as
	declare @lastTestRun int

	insert into TestRuns (Description, StartAt, EndAt) 
	values (@operation + ' insert test', @start, @end)
	
	set @lastTestRun = (select max(TestRunID) from TestRuns)

	if @testedEntityName like '%Table'
	begin
		insert into TestRunTables
		values(@lastTestRun, (select TableId from dbo.Tables where Name = @testedEntityName), @start, @end)
	end
	if @testedEntityName like '%View'
	begin
		insert into TestRunViews
		values (@lastTestRun, (select ViewId from dbo.Views where Name = @testedEntityName), @start, @end)
	end
go

CREATE OR ALTER PROCEDURE RunAllTests @nrOfRows int
as
	if @nrOfRows < 1
	begin
		RAISERROR('Invalid number of rows.', 16, 1)
	end

	declare @lastTestRun int
	declare @start datetime
	declare @end datetime


	-- Insert tests --
	set @start = GETDATE()
	exec InsertElements @tableName = 'ReleaseLabels', @nrOfRows = @nrOfRows
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'ReleaseLabelsTable', @operation = 'insert', @start = @start, @end = @end 

	set @start = GETDATE()
	exec InsertElements @tableName = 'Albums', @nrOfRows = @nrOfRows
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'AlbumsTable', @operation = 'insert', @start = @start, @end = @end 
	
	set @start = GETDATE()
	exec InsertElements @tableName = 'SongsArtists', @nrOfRows = @nrOfRows
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'SongsArtistsTable', @operation = 'insert', @start = @start, @end = @end 


	-- Delete tests --
	set @start = GETDATE()
	exec DeleteRows @tableName = 'SongsArtists', @nrOfRows = @nrOfRows
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'SongsArtistsTable', @operation = 'delete', @start = @start, @end = @end

	set @start = GETDATE()
	exec DeleteRows @tableName = 'ReleaseLabels', @nrOfRows = @nrOfRows
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'ReleaseLabelsTable', @operation = 'delete', @start = @start, @end = @end 

	set @start = GETDATE()
	exec DeleteRows @tableName = 'Albums', @nrOfRows = @nrOfRows
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'AlbumsTable', @operation = 'delete', @start = @start, @end = @end 
	

	set @start = GETDATE()
	exec SelectView @viewName = 'OneTableView'
	exec LogTest @testedEntityName = 'AlbumsTable', @operation = 'delete', @start = @start, @end = @end 
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'OneTableView', @operation = 'select', @start = @start, @end = @end 
	
	set @start = GETDATE()
	exec SelectView @viewName = 'TwoTablesView'
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'TwoTablesView', @operation = 'select', @start = @start, @end = @end 

	set @start = GETDATE()
	exec SelectView @viewName = 'TwoTablesGroupByView'
	set @end = GETDATE()
	exec LogTest @testedEntityName = 'TwoTablesGroupByView', @operation = 'select', @start = @start, @end = @end 


	exec DeleteAll @tableName = 'Songs'
	exec DeleteAll @tableName = 'ReleaseLabels'
	exec DeleteAll @tableName = 'Albums'
	exec DeleteAll @tableName = 'Artists'
	exec DeleteAll @tableName = 'SongsArtists'
go

exec RunAllTests @nrOfRows = 10
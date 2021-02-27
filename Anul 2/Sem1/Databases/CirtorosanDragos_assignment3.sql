use [ET-Music]


-- create versioning procedures --
create procedure version1 as
go

create procedure version1_undo as
go

create procedure version2 as
go

create procedure version2_undo as
go

create procedure version3 as
go

create procedure version3_undo as
go

create procedure version4 as
go

create procedure version4_undo as
go

create procedure version5 as
go

create procedure version5_undo as
go

create procedure version6 as
go

create procedure version6_undo as
go

create procedure version7 as
go

create procedure version7_undo as
go


-- implement versioning procedures --
alter procedure version1
as
	alter table Songs
	alter column [Length] int
	RAISERROR( 'Changed song length to int.', 1, 1 )
go

alter procedure version1_undo
as
	alter table Songs
	alter column [Length] float
	RAISERROR( 'Changed song length to float.', 1, 1 )
go

alter procedure version2
as
    alter table Artists
    add Height float
    RAISERROR( 'Added height column for artists.', 1, 1 )
go

alter procedure version2_undo
as
    alter table Artists
    drop column Height
    RAISERROR( 'Removed height column for artists.', 1, 1 )
go

alter procedure version3
as
	alter table Songs
	add constraint DEFAULT_IsInTop default 0 for IsInTop
    RAISERROR( 'Set default IsInTop flag to false.', 1, 1 )
go

alter procedure version3_undo
as
	alter table Songs
	drop constraint DEFAULT_IsInTop
    RAISERROR( 'Set default IsInTop flag to true', 1, 1 )
go

alter procedure version4
as
	alter table ReleaseLabels
	drop constraint PK_ReleaseLabels
    RAISERROR( 'Removed primary key from ReleaseLabels', 1, 1 )
go

alter procedure version4_undo
as
	alter table ReleaseLabels
	add constraint PK_ReleaseLabels primary key (Id)
    RAISERROR( 'Added primary key to ReleaseLabels', 1, 1 )
go

alter procedure version5
as
	alter table Albums
	add constraint CK_UniqueTitle unique (Title)
    RAISERROR( 'Added candidate key to Albums', 1, 1  )
go

alter procedure version5_undo
as
	alter table Albums
	drop constraint CK_UniqueTitle
    RAISERROR( 'Removed candidate key from Albums.', 1, 1 )
go

alter procedure version6
as
	alter table Playlists
	drop constraint FK_Playlists_Users
    RAISERROR( 'Removed foreign key for CreatingUserId from Playlists.', 1, 1 )
go

alter procedure version6_undo
as
	alter table Playlists
    add constraint FK_Playlists_Users foreign key (CreatingUserId) references Users(Id)
    RAISERROR( 'Added foreign key for CreatingUserId into Playlists.', 1, 1 )
go

alter procedure version7
as
	create table UnreleasedSongs (Id int primary key identity(1, 1),
						  Title nvarchar(50),
						  ReleaseDate datetime,
						  ArtistId int foreign key references Artists(Id))
    RAISERROR( 'Added UnreleasedSongs table.', 1, 1 )
go

alter procedure version7_undo
as
	drop table UnreleasedSongs
    RAISERROR( 'Dropped UnreleasedSongs table.', 1, 1 )
go


-- create helper procedures --
create procedure getCurrentVersion
	@version int output
as
go

create procedure goToNextVersion 
	@version int
as
go

create procedure goToPreviousVersion 
	@version int
as
go

create procedure updateVersion
	@newVersion int
as
go

create procedure logVersionChange
	@oldV int,
	@newV int
as
go


-- implement helper procedures --
alter procedure getCurrentVersion
	@version int output
as
	select @version = v.version
	from version v
go

alter procedure goToNextVersion 
	@version int
as
	if @version = 0
		exec version1
	else if @version = 1
		exec version2
	else if @version = 2
		exec version3
	else if @version = 3
		exec version4
	else if @version = 4
		exec version5
	else if @version = 5
		exec version6
	else if @version = 6
		exec version7
go

alter procedure goToPreviousVersion 
	@version int
as
	if @version = 1
		exec version1_undo
	else if @version = 2
		exec version2_undo
	else if @version = 3
		exec version3_undo
	else if @version = 4
		exec version4_undo
	else if @version = 5
		exec version5_undo
	else if @version = 6
		exec version6_undo
	else if @version = 7
		exec version7_undo
go

alter procedure updateVersion
	@newVersion int
as
	update version
	set version = @newVersion
go

alter procedure logVersionChange
	@oldV int,
	@newV int
as
	insert into VersionLog
	values (@oldV, @newV, SYSDATETIME())
go


-- user-called procedure --
create procedure changeVersion 
	@v int
as
go

alter procedure changeVersion 
	@v int
as
    if @v < 0 or @v > 7
        RAISERROR('Invalid version.', 20, 1)
	else
	begin
		declare @actualVersion int = 1

		exec getCurrentVersion @version = @actualVersion output

		declare @source int = @actualVersion
		if @source < @v
			while @source < @v
			begin
				exec goToNextVersion @version = @source
				set @source = @source + 1
			end
		else if @source > @v
			while @source > @v
			begin
				exec goToPreviousVersion @version = @source;
				set @source = @source - 1
			end
		else
			RAISERROR( 'Already at that version.', 1, 1 )
		exec updateVersion @newVersion = @v
		exec logVersionChange @oldV = @actualVersion, @newV = @v
	end
go

use [et-music]


---- Session 1 ----
SELECT @@SPID

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM SYS.dm_tran_locks where request_owner_type='TRANSACTION'



-- Dirty Reads --
insert into Songs(Id, Title, Length, IsInTop) values(1, 'Green Initial', 45, 1)
delete from Songs

begin tran _dirtyRead1
	update Songs
	set Title = 'Green Modified'
	where Title = 'Green Initial'
rollback tran _dirtyRead1



-- Non repeatable reads --
INSERT INTO Songs(Id, Title, Length, IsInTop) VALUES (1, 'Red Initial', 24, 1)
DELETE FROM Songs

BEGIN TRANSACTION _nonRepeatableRead2
	UPDATE Songs
	SET Title = 'Red Modified'
	WHERE Title = 'Red Initial'
COMMIT TRANSACTION _nonRepeatableRead2



-- Phantom reads --
INSERT INTO Songs(Id, Title, Length, IsInTop) VALUES (1, 'Blue Initial', 24, 1)
DELETE FROM Songs

BEGIN TRANSACTION _phantomRead1
	SELECT * FROM Songs
	WHERE Title LIKE 'Blue%'

	SELECT * FROM Songs
	WHERE Title LIKE 'Blue%'
COMMIT TRANSACTION _phantomRead1



-- Deadlock --
insert into Songs(Id, Title, Length, IsInTop) values(1, 'Reep', 50, 1)
insert into Songs(Id, Title, Length, IsInTop) values(2, 'Peer', 50, 0)

delete from Songs

set DEADLOCK_PRIORITY HIGH
set DEADLOCK_PRIORITY LOW
set DEADLOCK_PRIORITY MEDIUM

BEGIN TRAN _deadlock1
	update songs set Title='test' where Id=1 
	update songs set Title='test' where Id=2 
COMMIT TRAN _deadlock1


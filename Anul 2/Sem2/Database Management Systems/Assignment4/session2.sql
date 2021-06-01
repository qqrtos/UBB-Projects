use [et-music]


---- Sessiun 2 ----
SELECT @@SPID

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM SYS.dm_tran_locks where request_owner_type='TRANSACTION'



-- Dirty Reads --
set transaction isolation level READ UNCOMMITTED
set transaction isolation level READ COMMITTED

BEGIN TRANSACTION _dirtyRead2
	SELECT * FROM Songs

	SELECT * FROM Songs
COMMIT TRANSACTION _dirtyRead2 



-- Non repeatable reads --
set transaction isolation level READ COMMITTED
set transaction isolation level REPEATABLE READ

BEGIN TRANSACTION _nonRepeatableRead1
	SELECT * FROM Songs

	SELECT * FROM Songs
COMMIT TRANSACTION _nonRepeatableRead1



-- Phantom reads --
set transaction isolation level REPEATABLE READ
set transaction isolation level SERIALIZABLE

BEGIN TRANSACTION _phantomRead2
	INSERT INTO Songs(Id, Title, Length, IsInTop) VALUES (2, 'Blue New', 56, 0)
COMMIT TRANSACTION _phantomRead2



-- Deadlock --
BEGIN TRAN _deadlock2
	update songs set Title='test' where Id = 2
	update songs set Title='test' where Id = 1
COMMIT TRAN _deadlock2


use [ET-Music]

create table Ta (
	aid int PRIMARY KEY,
	a2 int UNIQUE
)

create table Tb (
	bid int PRIMARY KEY,
	b2 int
)

CREATE TABLE Tc (
	cid int PRIMARY KEY,
	aid int FOREIGN KEY REFERENCES Ta(aid),
	bid int FOREIGN KEY REFERENCES Tb(bid)
)


-- a)
select aid from Ta order by aid -- clustered index scan

select aid from Ta where aid > 4 -- clustered index seek

select a2 from Ta -- nonclustered index scan

select a2 from Ta where a2 > 4 -- nonclustered index seek

select * from Ta -- table scan


-- b)
select b2 from Tb where b2 = 3 -- clustered index scan

-- drop index indxB2 on Tb
create nonclustered index indexB2 on Tb(b2)
select b2 from Tb where b2 = 3 -- nonclustered index seek


-- c)
CREATE OR ALTER VIEW VTbTc
AS
	select Tc.cid, Tc.bid from Tc
	inner join Tb on Tc.bid = Tc.bid
GO

select * from VTbTc -- clustered index scan on Tc, clustered index seek on Tb -> 11.4ms

-- drop index indxBID on Tc
create nonclustered index indxBID on Tc(bid)

select * from VTbTc -- nonclustered index scan on Tc, clustered index scan on Tb -> 10.1ms

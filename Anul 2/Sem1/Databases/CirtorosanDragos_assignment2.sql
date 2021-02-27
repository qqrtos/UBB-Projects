--insert into genres
insert into Assignment1_LibraryChain.dbo.Genres values ('History')
insert into Assignment1_LibraryChain.dbo.Genres values ('Philosophy')
insert into Assignment1_LibraryChain.dbo.Genres values ('Fiction')

select * from Assignment1_LibraryChain.dbo.Genres


--insert into authors
insert into Assignment1_LibraryChain.dbo.Authors values 
('Ion Creanga :)))', '11-10-1950')
insert into Assignment1_LibraryChain.dbo.Authors values 
('George Orwell', '11-10-1900')

select * from Assignment1_LibraryChain.dbo.Authors


--insert into membership cards
insert into Assignment1_LibraryChain.dbo.MembershipCard values
('05-30-2016')
insert into Assignment1_LibraryChain.dbo.MembershipCard values
('12-22-2017')

select * from Assignment1_LibraryChain.dbo.MembershipCard


--insert into clients
insert into Assignment1_LibraryChain.dbo.Clients values
(4, 'Bodor', 'Ion', '05-22-2000')
insert into Assignment1_LibraryChain.dbo.Clients values
(4, 'Ion', 'Marian', '11-12-1998')
insert into Assignment1_LibraryChain.dbo.Clients values
(4, 'Gicu', 'Petrica', '05-10-1980')
insert into Assignment1_LibraryChain.dbo.Clients values
(4, 'George Orwell', 'Gg', '05-10-1980')

select * from Assignment1_LibraryChain.dbo.Clients


--insert into addresses
insert into Assignment1_LibraryChain.dbo.Addresses values
(1, 'Bucharest', '1 decembrie', 12)
insert into Assignment1_LibraryChain.dbo.Addresses values
(2, 'Cluj', 'Piezisa', 322)
insert into Assignment1_LibraryChain.dbo.Addresses values
(3, 'Sibiu', 'Dumbrava', 9)

select * from Assignment1_LibraryChain.dbo.Addresses


--insert into physical libraries
insert into Assignment1_LibraryChain.dbo.PhysicalLibraries values
(1, 'Carturesti')
insert into Assignment1_LibraryChain.dbo.PhysicalLibraries values
(3, 'Okian')

select * from Assignment1_LibraryChain.dbo.PhysicalLibraries


--insert into books
insert into Assignment1_LibraryChain.dbo.Books values
(1, 'The life of Pi', '10-09-2011')
insert into Assignment1_LibraryChain.dbo.Books values
(3, 'The three body problem', '11-22-2002')

select * from Assignment1_LibraryChain.dbo.Books


--insert into books/genres
insert into Assignment1_LibraryChain.dbo.BooksGenres values
(1, 1)
insert into Assignment1_LibraryChain.dbo.BooksGenres values
(2, 1)
insert into Assignment1_LibraryChain.dbo.BooksGenres values
(2, 3)

select * from Assignment1_LibraryChain.dbo.BooksGenres


--insert into books/authors
insert into Assignment1_LibraryChain.dbo.BooksAuthors values
(1, 1)
insert into Assignment1_LibraryChain.dbo.BooksAuthors values
(1, 2)
insert into Assignment1_LibraryChain.dbo.BooksAuthors values
(2, 1)
insert into Assignment1_LibraryChain.dbo.BooksAuthors values
(2, 2)

select * from Assignment1_LibraryChain.dbo.BooksAuthors


--insert into workers
insert into Assignment1_LibraryChain.dbo.Workers values
(1, 'George Orwell','G','02-03-2010')
insert into Assignment1_LibraryChain.dbo.Workers values
(2, 'Bodor','Ion','03-04-2005')

select * from Assignment1_LibraryChain.dbo.Workers


update Assignment1_LibraryChain.dbo.Addresses 
set Street = 'Fabricii'
where City like 'Cluj%'

uPdAtE Assignment1_LibraryChain.dbo.Books
set Title = 'Muh Hurt'
where PublicationDate between '01-01-2010' and '12-30-2011' 
	and ClientId is not NULL


-- QUERIES --

-- a) --
-- select all authors and workers --
select Name from Assignment1_LibraryChain.dbo.Authors
union
select Name from Assignment1_LibraryChain.dbo.Workers
order by Name

-- select clients older than smth and authors born before smth --
select Name, DateOfBirth from Assignment1_LibraryChain.dbo.Clients
where DateOfBirth > '01-01-1999'
union all
select Name, DateOfBirth from Assignment1_LibraryChain.dbo.Authors
where DateOfBirth <= '01-01-1920'

-- b) --
-- select people that are both authors and clients of a library --
select Name from Assignment1_LibraryChain.dbo.Clients
where Name in (select Name from Assignment1_LibraryChain.dbo.Authors)

-- intersection between authors and clients name --
select Name from Assignment1_LibraryChain.dbo.Clients
intersect
select Name from Assignment1_LibraryChain.dbo.Authors

-- c) --
-- select the clients that are not workers of the library --
select Name from Clients
except
select Name from Workers
order by Name desc

-- d) --
-- select all the books and the clients that borrowed them (null if not borrowed) --
select Title, Clients.Name from Books
left join Clients on Books.ClientId = Clients.Id

-- select workers that are also clients and show the library they work in --
select Workers.Name as WorkerName, PhysicalLibraries.Name as LibraryName from Workers
inner join PhysicalLibraries on PhysicalLibraries.Id = Workers.LibraryId
inner join Clients on Workers.Name = Clients.Name and Workers.Surname = Clients.Surname

-- select all books and show their genres --
select Type, Books.Title from Genres
right join BooksGenres on Genres.Id = BooksGenres.GenreId
right join Books on Books.Id = BooksGenres.BookId
order by Type desc

-- select all authors that have written with the genres they've written and the corresponding books --
select Authors.Name, Books.Title, Genres.Type from Authors
full join BooksAuthors on BooksAuthors.AuthorId = Authors.Id
full join Books on Books.Id = BooksAuthors.BookId
full join BooksGenres on BooksGenres.BookId = Books.Id
full join Genres on Genres.Id = BooksGenres.GenreId

-- e) --
-- select the workers that have a name which is a book title --
select Workers.Name, Workers.Surname from Workers where workers.Name in (
	select Books.Title from Books
)

-- select the common names between authors, workers and clients
select Workers.Name from Workers
where Workers.Name in (
	select Authors.Name from Authors
	where Authors.Name in (
		select Clients.Name from Clients
	)
)

-- f) -- 
-- select authors that have written at more than 1 book --
select Name, DateOfBirth from Authors
where exists (
	select * from BooksAuthors
	where Authors.Id = BooksAuthors.AuthorId
	group by AuthorId
	having count(*) > 1
) order by Name desc

-- select only the clients that have rented a book --
select Name, Surname, DateOfBirth from Clients as c
where exists (
	select * from Clients
	inner join Books on Clients.Id = Books.ClientId
	where c.Id = Clients.Id
)

-- g)--
-- select the name and date of birth for authors that have a matching name with at least a client --
select t.authname, t.adob from (
	select Name as authname , DateOfBirth as adob from Authors 
	where Authors.Name in (
		select Clients.Name from Clients
	)
) as t

-- select all distinct dates of birth for each client --
select c.DateOfBirth from (
	select Id, t.DateOfBirth from (
		select distinct DateOfBirth from Clients
	) as t, Clients
	where t.DateOfBirth = Clients.DateOfBirth
) as c
order by c.DateOfBirth


-- h) --
-- show the books corresponding to more than 1 genre --
select Books.Title from Books
inner join BooksGenres on BooksGenres.BookId = Books.Id
inner join Genres on Genres.Id = BooksGenres.GenreId
group by Books.Title
having Count(*) > 1

-- see how many workers with the same name there are --
select count(*) as nr, Name from Workers
group by Name

-- select the books that are publish later than average and show how many of them are published in matching days --
select Count(*) as nr, PublicationDate from Books
group by PublicationDate
having PublicationDate > (
	select CAST(Avg(CAST(PublicationDate as int)) as smalldatetime) from Books
)

-- i) --
-- select the books borrowed by clients younger than smth --
select Title from Books
where Books.ClientId = ANY (select Id from Clients where DateOfBirth > '1990-01-01')

-- same as above, but with aggregation operators --
select Title from Books
inner join Clients on Clients.Id = Books.ClientId
group by Title
having CAST(Min(CAST(DateOfBirth as int)) as smalldatetime) > '1990-01-01'

-- select the books that are published before all the clients were bron (old books) --
select Title, PublicationDate from Books
where Books.PublicationDate < ALL (select Clients.DateOfBirth from clients)

-- same as above --
select Title, PublicationDate from Books, Clients
group by Books.Title, PublicationDate
having Books.PublicationDate < min(Clients.DateOfBirth)

create database Transport
go

create table driver
(dno varchar(18) not null primary key,
dname varchar(10) not null,
dsex varchar(2) null default 'ÄÐ' check(dsex='ÄÐ' or dsex='Å®'),
dbir varchar(10) null,
dadd varchar(50) null,
dfirstdate varchar(10) null,
dtype varchar(20) null,
duse varchar(50) null,
dpass varchar(50) not null
)
create table cars
(cno varchar(20) not null primary key,
ctype varchar(20) not null,
cpeople varchar(10) null,
color varchar(20) null,
cowner varchar(10) null,
cengine varchar(20) null,
cweight varchar(10) null,
cmodel varchar(30) null,
cvin varchar(20) null,
cregister varchar(10) null default getdate(),
cerdate varchar(10) null 
) 
create table run
(
dno varchar(18) not null,
runtime varchar(10) not null,
endtime varchar(10) null,
cno varchar(20) not null,
distance varchar(10) null,
oil varchar(10) null,
primary key(dno,runtime),
)

create table repair
(
cno varchar(20) not null,
rfirstime varchar(10) not null,
rendtime varchar(10) null,
rname varchar(30) null,
content varchar(50) null, 
rmoney varchar(10) null,
slave varchar(20) null,
rmore text null,
primary key(cno,rfirstime),
)

create table accident
(
dno varchar(18) not null,
time varchar(10) not null,
cno varchar(20) not null,
address varchar(50) null,
reason varchar(50) null,
ocno varchar(18) null,
odept varchar(50) null,
solution text null,
amoney varchar(10) null,
amore text null,
primary key(dno,time),
)
create table manageruser
(
id varchar(50) not null primary key,
password varchar(50) not null
)
 

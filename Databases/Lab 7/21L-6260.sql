CREATE TABLE [dbo].[Card](
	[cardNum] [varchar](20) NOT NULL,
	[cardTypeID] [int] NULL,
	[PIN] [varchar](4) NOT NULL,
	[expireDate] [date] NOT NULL,
	[balance] [float] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[cardNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[CardType]    Script Date: 3/22/2023 10:10:05 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[CardType](
	[cardTypeID] [int] NOT NULL,
	[name] [varchar](15) NULL,
	[description] [varchar](40) NULL,
PRIMARY KEY CLUSTERED 
(
	[cardTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Transactions]    Script Date: 3/22/2023 10:10:05 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Transactions](
	[transId] [int] NOT NULL,
	[transDate] [date] NOT NULL,
	[cardNum] [varchar](20) NULL,
	[amount] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[transId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UserCard]    Script Date: 3/22/2023 10:10:05 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserCard](
	[userID] [int] NULL,
	[cardNum] [varchar](20) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[cardNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Users]    Script Date: 3/22/2023 10:10:05 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[userId] [int] NOT NULL,
	[name] [varchar](20) NOT NULL,
	[phoneNum] [varchar](15) NOT NULL,
	[city] [varchar](20) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[userId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Card]  WITH CHECK ADD FOREIGN KEY([cardTypeID])
REFERENCES [dbo].[CardType] ([cardTypeID])
GO
ALTER TABLE [dbo].[Transactions]  WITH CHECK ADD FOREIGN KEY([cardNum])
REFERENCES [dbo].[Card] ([cardNum])
GO
ALTER TABLE [dbo].[UserCard]  WITH CHECK ADD FOREIGN KEY([cardNum])
REFERENCES [dbo].[Card] ([cardNum])
GO
ALTER TABLE [dbo].[UserCard]  WITH CHECK ADD FOREIGN KEY([userID])
REFERENCES [dbo].[Users] ([userId])
GO







INSERT [dbo].[Users] ([userId], [name], [phoneNum], [city]) VALUES (1, N'Ali', N'03036067000', N'Narowal')
GO
INSERT [dbo].[Users] ([userId], [name], [phoneNum], [city]) VALUES (2, N'Ahmed', N'03036047000', N'Lahore')
GO
INSERT [dbo].[Users] ([userId], [name], [phoneNum], [city]) VALUES (3, N'Aqeel', N'03036063000', N'Karachi')
GO
INSERT [dbo].[Users] ([userId], [name], [phoneNum], [city]) VALUES (4, N'Usman', N'03036062000', N'Sialkot')
GO
INSERT [dbo].[Users] ([userId], [name], [phoneNum], [city]) VALUES (5, N'Hafeez', N'03036061000', N'Lahore')
GO


INSERT [dbo].[CardType] ([cardTypeID], [name], [description]) VALUES (1, N'Debit', N'Spend Now, Pay Now')
GO
INSERT [dbo].[CardType] ([cardTypeID], [name], [description]) VALUES (2, N'Credit', N'Spend Now, Pay later')
GO

INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1234', 1, N'1770', CAST(N'2022-07-01' AS Date), 43025.31)
GO
INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1235', 1, N'9234', CAST(N'2020-03-02' AS Date), 14425.62)
GO
INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1236', 1, N'1234', CAST(N'2019-02-06' AS Date), 34325.52)
GO
INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1237', 2, N'1200', CAST(N'2021-02-05' AS Date), 24325.3)
GO
INSERT [dbo].[Card] ([cardNum], [cardTypeID], [PIN], [expireDate], [balance]) VALUES (N'1238', 2, N'9004', CAST(N'2020-09-02' AS Date), 34025.12)
GO

INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (1, N'1234')
GO
INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (1, N'1235')
GO
INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (2, N'1236')
GO
INSERT [dbo].[UserCard] ([userID], [cardNum]) VALUES (3, N'1238')
GO
Insert  [dbo].[UserCard] ([userID], [cardNum]) VALUES (4, N'1237')

INSERT [dbo].[Transactions] ([transId], [transDate], [cardNum], [amount]) VALUES (1, CAST(N'2017-02-02' AS Date), N'1234', 500)
GO
INSERT [dbo].[Transactions] ([transId], [transDate], [cardNum], [amount]) VALUES (2, CAST(N'2018-02-03' AS Date), N'1235', 3000)
GO
INSERT [dbo].[Transactions] ([transId], [transDate], [cardNum], [amount]) VALUES (3, CAST(N'2020-01-06' AS Date), N'1236', 2500)
GO
INSERT [dbo].[Transactions] ([transId], [transDate], [cardNum], [amount]) VALUES (4, CAST(N'2016-09-09' AS Date), N'1238', 2000)
GO
INSERT [dbo].[Transactions] ([transId], [transDate], [cardNum], [amount]) VALUES (5, CAST(N'2020-02-10' AS Date), N'1234', 6000)








/*Q1*/
create view[userdetail] as 
select * from Users
go;
select * from [userdetail]	



/*Q2*/
create view[users with cards] as
select  name, phoneNum number, city,cardNum from Users inner join Usercard
on users.userId=UserCard.userID  
select * from [users with cards] 



/*Q3*/
create procedure specific_user_data @user varchar(20)
as 
select * from Users where name=@user
Exec specific_user_data @user='ahmed'



/*Q4*/
create procedure minBalance
 @min float output
 as 
 Begin
 select @min=min(Balance) from Card
 END
 
 declare @min float
 exec minBalance @min output
 select @min as Minimum



 /*Q5*/
 create procedure no_of_cards 
 @name varchar(20),
 @userid int,
 @no int output 
 as

 Begin 
 Select @no=count(UserCard.userID) from UserCard
 inner join Users on 
 Users.userId=UserCard.userID
 where Users.name=@name and Users.userId=@userid
 END
 
 declare @no int ;

 exec no_of_cards @name='Ali',@userid=1, @no=@no output
 select @no
 


 /*Q6*/
 create procedure login
 @cardnum varchar(20),
 @pin varchar(4),
 @status int output
 as 
Begin
 if EXISTS (select * from Card where card.cardNum=@cardnum and card.PIN=@pin)
	set @status=1
 else 
	set @status=0
END

declare @St int

exec login @cardnum='1234',@pin='1770',@status=@St output
select @st as status



/*Q7*/
create procedure update_pin
@cardnum varchar(20),
@oldpin varchar(4),
@newpin varchar(4),
@result varchar(10) output
as
BEGIN
declare @check int
select @check=count(*) from card where card.cardNum=@cardnum and card.PIN=@oldpin
if (@check=0) or (len(@newpin)<>4)
	begin
	set @result='ERROR'
	return ;
	end
else 
begin
	update card set pin=@newpin  where card.cardNum=@cardnum and card.PIN=@oldpin
	set @result='updated'
	end
END
declare @res varchar(10)
exec update_pin @cardnum='1234',@oldpin='1770',@newpin='1111',@result=@res output
select @res as result



/*Q8*/
create procedure withdraw
@cardnum varchar(20),
@pin varchar(4),
@amount float,
@result varchar(10) output
as 
BEGIN
declare @St int
exec login @cardnum=@cardnum,@pin=@pin,@status=@St output
if (@St=1)
 begin
 DECLARE @max INT
 SELECT @max = MAX(transid)
 FROM Transactions
 insert into Transactions values(@max+1,GETDATE(),@cardnum,@amount)
 update card set balance=balance-@amount where cardNum=@cardnum and PIN=@pin
 set @result='successful'
end 

else
 set @result='ERROR'

END

declare @result varchar(10)
exec withdraw @cardnum='1235',@pin='9234',@amount='18700',@result=@result output
select @result as result 



	







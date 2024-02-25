
/* Q1*/
select * from customers where city='New York'


/* Q2*/
select*from customers where customer_name like '%John%'and (city='London' or city='Paris' or city='New York')


/* Q3*/
select *from customers where city ='London' or city='New York'


/* Q4*/
select*from orders where purch_amt>500


/* Q5*/
select*from salesman where substring(name,2,1)='a'


/* Q6*/
update salesman set commission=commission+0.5 where city ='San Jose'


/* Q7*/
select * from orders order by ord_date desc


/* Q8*/
SELECT SUBSTRING(name, 1, CHARINDEX(' ', name) - 1) AS firstname
FROM salesman;


/* Q9*/
SELECT * FROM orders 
WHERE MONTH(ord_date) = 1;


/* Q10*/
SELECT YEAR(ord_date) AS year, 
       DATEPART(wk, ord_date) AS week, 
       DATEPART(dayofyear, ord_date) AS dayofyear, 
       MONTH(ord_date) AS month, 
       DAY(ord_date) AS day, 
       DATEPART(weekday, ord_date) AS weekday
FROM orders
WHERE MONTH(ord_date) = 10;


/* Q11*/
update  orders set purch_amt=purch_amt*3 where month(ord_date)=10


/* Q12*/
SELECT customers.customer_id
FROM customers
INNER JOIN orders ON customers.customer_id = orders.customer_id
WHERE YEAR(ord_date) IN (2011, 2013);


/* Q13*/
select top(5)* from salesman order  by  commission desc
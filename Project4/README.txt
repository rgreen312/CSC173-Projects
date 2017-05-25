Sam Triest - striest@u.rochester.edu
Ryan Green - rgreen14@u.rochester.edu
William Wilson - wwils11@u.rochester.edu	

To run:
./main.sh

Project Description:
This project is a simple implementation of a database data structure. The database in this project is based on the five tables given in the Aho and Ullman book. 

Part 1:
According to the project description, we implemented individual structs to represent schema and stored each in a linked list as a table. All of the tables are hashed on a specific attributes to optimize querying in part 2. All of the tables support basic insert, lookup and delete functions, as well as saving to and reading from a file.

Part 2:
For this part of the project, we implemented functions that take queries as input, and return the results in the database. The two functions that we implemented answer the queries, “Where is ‘StudentName’ at Time on Day?” and “What grade did ‘StudentName’ get in Course?” These functions parse the strings they are passed to determine whether the input is valid. They then get the elements of the string to be used in the relational algebra of these queries. To perform the relational algebra that answers these questions, a combination of other functions we have written and loops are used. 

Part 3:
For this part of the project, we implemented functions that could select data from each table and showed examples. As well, we implemented functions that projected data and joined tables as well, which also have examples of implementation and use in the code itself. The projection gets specific attributes from the relation given, while the join function combines tables on a certain given parameter.

We used a string_hash generic function found at: https://github.com/fragglet/c-algorithms/blob/master/src/hash-string.c
It’s a short implementation.

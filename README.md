# CS325GA3
The way I modified this was really lazy, because I wanted to change as little as possible in the Prim's algorithm from geeksforgeeks.
Basically, I noticed the fact that at the bottom of the algorithm, there's a call to this function: printArr(parent, V). If you go up to the function definition, you can see that, after I added some stuff, it prints arr[i] and i, Which together are edges from verges arr[i] to i. I have no clue what arr[i] is or how it's calculated, but I know that's one of the vertices. I made a new struct called Pair to store the vertices and act like an edge, and made a vector of Pairs called pairs to store all the pairs. I'm sure there's a way to actually modify the prim's alg here to add Edges and remove edges or whatever, but I was really lazy and didn't want to mess with it.

In the actual algorithm--not prim's but where i start calculating mst1, mst2 and mst3 in main, I didn't do anything special to calculate mst1. I just used the algorithm that I stole.
IMPORTANT NOTE: in this Prim's algorithm, printarray is called every time the algorithm finishes, and it updates pairs with the edges in the MST. Of course, the pairs use the same vertices as in the original adjacency matrix, so that makes it easier. Since for mst1 I only had to run it once, I didn't have to clear the pairs vector. for mst1, i calculate the totals by looping through the pairs array and adding up the values of the graph at the indices for each pair (x,y) or (v1,v2). I then create a struct MST called mst1 (I defined the struct near the printArr function) and pass it the values, and then print out the total. that's it for mst1.

for mst2, the idea is kind of the same:

Use Prim's to find MST.
For each edge in MST:
	Remove edge from graph
	Calculate MST' on MST
	Keep track of smallest MST
	Add edge back to graph
Return the smallest MST.*/

in the for loop, i loop through all the pairs in mst1 and add all the edges in the original graph and mst1 without the current pair in the loop (Remove one edge at a time from graph). I do this for all pairs in mst1.pairs. For each iteration, I create a new MST mst and pass it the weight, the pairs (which are updated with each new iteration because prim's alg calls printArr, which clears the previous pairs and adds the new ones each prim's is completed), and then I add it to a vector called mstVec, which will store all of the possible mst2 MSTs.

After the loop through the pairs of mst1 is done, I look for the MST with the smallest weight in mstVec that's NOT the same weight as the last MST. this was actually really annoying because you can have cases where the mst1,2,and 3 are the same, so basically if all of mstVec is full of MSTs that have the same weight--mst1's weight--then that's the mst2 weight as well. if there's even one that's greater than mst1's weight, then that's mst2's weight.

Same process for mst3. The loop to find the smallest value checks the entire mstVec array to see if there are any weights that are the same.

and uhhh yeah that's it i guess

package a4q2;

import java.util.LinkedList;
import java.util.Set;

public class ShapeGraph extends Graph<Shape> {	
	
	public ShapeGraph() {
	}
 	
	public void resetVisited() {
		Set<String>  vertexKeySet =  vertexMap.keySet(); 
		for( String key : vertexKeySet ){
			vertexMap.get(key).visited = false;
		}				
	}
	
	
	/**
	 * Returns a list of lists, each inner list is a path to a node that can be reached from a given node
	 * if the total area along the path to that node is greater than the threshold.
	 * Your solution must be a recursive, depth first implementation for a graph traversal.
	 * The Strings in the returned list of lists should be the vertex labels (keys).
	 */
	
	public LinkedList<LinkedList<String>> traverseFrom(String key, float threshold)
	{
		LinkedList<LinkedList<String>> masterList = new LinkedList<>();
		LinkedList<LinkedList<String>> allpaths = new LinkedList<>();
		//   ADD YOUR CODE HERE.  (IF YOU WISH TO ADD A HELPER METHOD, THEN ADD IT AFTER THIS METHOD.)
        resetVisited();
		Vertex<Shape> currentNode = vertexMap.get(key);
		LinkedList<String> list = new LinkedList<String>();
        Dfs(currentNode,allpaths,list);
        //masterList.removeLast();
        //Dfs(currentNode, output);
        for(LinkedList<String> path : allpaths){
        	//System.out.println(path);
        	if(sumList(path) >= threshold){
        		masterList.add(path);
        	}
        }
		return masterList;
		
	}
	
	public void Dfs(Vertex<Shape> v, LinkedList<LinkedList<String>> masterlist, LinkedList<String> list){ 

		v.visited =true;
		list.add(v.getKey());
//		if(list.size() != 1){
//			masterlist.add((LinkedList<String>) list.clone());
//		}
//		

        for(Edge e : v.adjList){
        	if(!e.getEndVertex().visited){
            	Dfs(e.getEndVertex(), masterlist,list);
        	}

        }
        
        masterlist.add((LinkedList<String>) list.clone());
        list.removeLast();

	}
	
	public float sumList(LinkedList<String> path){
		float sum = 0;
		for(String s : path){
			sum += vertexMap.get(s).element.getArea();
		}
		return sum;
		
	}
	
}








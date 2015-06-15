

import java.util.*;
import java.util.concurrent.*;

public class Graph<T extends Node>{

	PrioQueue pq;
	MFSet set;

	
	
	LinkedList<T> nodes;
	HashMap<T, Integer> indexies;

	private int edgesCount = 0;
	ConcurrentLinkedQueue<T> connectingNodesQueue;
	ConcurrentLinkedQueue<T> disconnectingNodesQueue;

	
	public Graph(T [] nodesArray){

		connectingNodesQueue = new ConcurrentLinkedQueue<T>();
		disconnectingNodesQueue = new ConcurrentLinkedQueue<T>();
		nodes = new LinkedList<T>();

		// make all edges and add to priority queue
		pq = new PrioQueue(new PrioQueue.Comparator(){
			
			@Override
			public int compare(Object elm1, Object elm2){
				double edge1 = ((Edge)elm1).cost();
				double edge2 = ((Edge)elm2).cost();
				if(edge1 > edge2){
					return 1;				
				}
				else if(edge1 < edge2){
					return -1;				
				}
				return 0;
			}
		},
		createEdges(nodesArray)); // edges


		
		indexies = new HashMap<T, Integer>();
		for(int i = 0; i < nodesArray.length; i++){
			nodes.add(nodesArray[i]);
		}
		// set the current inexies for the MF set
		updateIndexies();
	
		// create the MFSet
		set = new MFSet<T>(nodes.size(), new MFSet.Indexer<T>(){
			@Override
			public int eval(T node){
				return indexies.get(node);	
			}			
		});

		
	}

	/*
	creates new hashmap of all nodes and their indexies in the MFSet
	*/
	private void updateIndexies(){
		indexies.clear();
		int index = 0;
		for(T node : nodes){
			indexies.put(node, new Integer(index));
			index ++;
		}
	}


	/*
	adds a new node to the graph
	*/
	public void connect(T node){
		if(!inQueue(node) && !nodes.contains(node)){
			connectingNodesQueue.add(node);
		}	
		
	}
	
	/*
	completely removes a node from the graph
	*/
	public void disconnect(T node){
		if(!inQueue(node)){
			disconnectingNodesQueue.add(node);
		}
			
	}

	public synchronized boolean inQueue(T node){
		return connectingNodesQueue.contains(node) || 
			disconnectingNodesQueue.contains(node);
	}

	/*
	Creates a new PrioQueue with edges between all 
	make edges between all nodes
	takes O(((n(n+1))/2)*n*logn)
	*/
	public Edge [] createEdges(T [] nodes){

	
		int length = nodes.length;
		Edge [] edgesArray = new Edge[(length*length+length)/2];

		for(int i = 0; i < length; i++){
			for(int j = i; j < length; j++){
				Edge e = new Edge(nodes[i], nodes[j]);
				edgesArray[edgesCount] = e;
				edgesCount ++;
			}
		}

		return edgesArray;
		
	}


	/*
	Reorders the edges according to the nodes current position
	*/
	public void updateState(){
		
		pq.reset(edgesCount);

		int removedEdges = decrease();
		int newEdges = increase();

		if(removedEdges+newEdges > 0){
			updateIndexies();
		}

		pq.decrease(removedEdges);
		edgesCount = edgesCount - removedEdges;
		set.reset(nodes.size());

	}


	/*
		returns number of added edges
	*/
	private int increase(){

		int added = 0;
		int size = connectingNodesQueue.size();

		for(int i = 0; i < size; i++){

			T node = connectingNodesQueue.poll();

			if(!indexies.containsKey(node)){
				// add node
				nodes.add(node);
				indexies.put(node, nodes.size());
				node.setConnected(true);
				// add its edges
				for(T n : nodes){
					edgesCount ++;
					pq.add(new Edge(node, n));
					added ++;
				}
			}
		}
		return added;
	}

	/*
	CAN BE OPTIMIZED FURTHER
	nodes.remove(node); takes O(n)

	returns number of removed edges
	*/
	private int decrease(){
		int decrease = 0;
		for(int i = 0; i < disconnectingNodesQueue.size(); i++){
			T node = disconnectingNodesQueue.poll();
			if(indexies.containsKey(node)){
				nodes.remove(node);
				node.setConnected(false);
				decrease += nodes.size()-i;
			}
		}
		return decrease;
	}
	

	public ArrayList<Edge> kruskals(double maxCost){

		ArrayList<Edge> clusters = new ArrayList<Edge>();
		int nbrOfNodes = this.nodes.size();
		while(nbrOfNodes > 1){
			Edge e = (Edge)pq.remove();
			if(e.cost() > maxCost){
				return clusters;
			}
			int u = set.find(e.node1);
			int v = set.find(e.node2);
			if(u != v){
				set.merge(e.node1,e.node2);
				nbrOfNodes --;
				clusters.add(e);
			}
		}
		return clusters;
	}

}

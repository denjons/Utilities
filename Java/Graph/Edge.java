import java.util.*;

public class Edge<T extends Node>{

	final T node1, node2;

	public Edge(T node1, T node2){
		this.node1 = node1;
		this.node2 = node2;
	}

	/*
	returns the current cost of an edge
	*/
	public double cost(){

		if(!this.node1.isConnected() || !this.node2.isConnected()){
			return Double.MAX_VALUE; 
		}

		double x = node1.xLocation() - node2.xLocation();
		double y = node1.yLocation() - node2.yLocation();

		return Math.sqrt(x*x+y*y);
	}

}

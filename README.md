# Food Delivery Management System

![FP](https://github.com/user-attachments/assets/f4e3c4a5-eb4d-4475-be71-63e376c7f593)


## Project Description

The **Food Delivery Management System** is a digital platform aimed at simplifying the management of food orders, deliveries, and billing for businesses in the food delivery sector. This project leverages **graphs** and **linked lists** to enhance the speed, efficiency, and accuracy of operations such as order tracking and distance calculation.  

By replacing manual and paper-based systems with this modern approach, the platform ensures seamless order management and improves customer satisfaction with faster delivery times and real-time tracking.  


## Key Features

- **Dynamic Order Management**:  
  Use a linked list to dynamically add, update, delete, and mark customer orders as delivered.  

- **Distance Calculation with Graphs**:  
  Utilize a graph-based 2D array system to calculate and display distances between delivery locations, optimizing routes for better efficiency.  

- **Billing and Summary**:  
  Automatically calculate total bills based on customer orders and display detailed summaries for customers.  

- **Order Status Tracking**:  
  Allow customers to check the current status of their orders.  

- **User-Friendly Interface**:  
  Simple menu-driven interface for managing orders, viewing distances, and accessing other system features.  


## Technologies and Tools Used

- **Programming Language**: C++  
- **Data Structures**:  
  1. **Graphs**:  
      - Represented as a 2D array to map distances between sectors.  
      - Used for delivery route optimization.  

  2. **Linked Lists**:  
      - Manage orders dynamically, with each node containing order details, customer information, and delivery status.  


## Data Structures and Complexity

### **Graph Operations**  
- **Representation**: 2D array (graph[7][7])  
- **Space Complexity**: O(n²)  
- **Time Complexity**:  
  - O(1) for updating distances.  
  - O(n) for retrieving distances.  

### **Linked List Operations**  
- **Structure**: Each node stores:  
  - Customer details  
  - List of ordered products and prices  
  - Delivery status  
- **Space Complexity**: O(n)  
- **Time Complexity**:  
  - O(1) for adding orders at the head or tail.  
  - O(n) for updating or canceling specific orders.  


## How It Works  

1. **Customer Interaction**:
   - Customers place orders by selecting items and quantities.  
   - They can view and update their orders in real-time.  

2. **Order Storage**:  
   - Orders are stored dynamically in a linked list, ensuring efficient management of an unpredictable number of orders.  

3. **Delivery Optimization**:  
   - The system calculates the shortest distance between sectors using a graph.  
   - Helps estimate delivery times and improves route planning.  

4. **Billing and Tracking**:  
   - Generates detailed billing summaries.  
   - Allows customers to track their order status until delivery.  


## Challenges Faced

1. **Graph Accuracy**:  
   - Ensuring accurate representation of distances between sectors.  

2. **Scalability**:  
   - Managing performance with large datasets or high-order volumes.  

3. **Input Validation**:  
   - Preventing invalid customer inputs and ensuring robust error handling.  

4. **Dynamic Data Management**:  
   - Handling real-time updates and cancellations efficiently.  

## Achievements

- Successfully implemented a graph-based system for sector distance calculations.  
- Developed a dynamic linked list for efficient order management.  
- Provided a functional and user-friendly interface for end-users.  

## Future Enhancements

1. **Enhanced Data Structures**:  
   - Use more advanced graph algorithms (e.g., Dijkstra’s) for scalability.  

2. **Mobile and Web Integration**:  
   - Create a mobile app or web interface for easier access.  

3. **Live Order Tracking**:  
   - Add GPS integration for real-time order location tracking.  

4. **Advanced Features**:  
   - Include promotional discounts, loyalty rewards, and multi-sector delivery options.  



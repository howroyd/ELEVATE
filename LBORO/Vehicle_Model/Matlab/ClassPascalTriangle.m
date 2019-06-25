classdef ClassPascalTriangle < handle
    %ClassPascal Summary of this class goes here
    %   Creates a Pascal triangle of a given order
    %   Construct with PascalTriangle(order)
    
    properties ( Access = private)
        order;
        triangle;
    end
    
    methods
        function obj = ClassPascalTriangle(order)
            %PascalTriangle Construct an instance of this class
            %   Creates a Pascal triangle of a given order
            
            obj.triangle = obj.set_pascal_triangle(order);
            obj.order = order;
        end
        
        function order = get_order(obj)
            order = obj.order;
        end
        
        function triangle = get_triangle(obj)
            triangle = obj.triangle;
        end
        
        function order = get_pascal_order(obj)
            order = obj.order;
        end
    end
    
    methods (Static)
        function pascal_triangle = set_order(order_requested)
            if (order_requested >= 1)
                pascal_triangle = ClassPascalTriangle.set_pascal_triangle(order_requested);
            else
                pascal_triangle = 0;
                error(sprintf("Couldn't create Pascal Triangle of order %f", order_requested));
            end
            
            if (pascal_triangle == 0)
                error("Undefined error");
            end
        end
        
        function triangle = set_pascal_triangle(order)
            
            % The first two rows are constant
            triangle(1, 1) = 1;
            triangle(2, 1 : 2) = [1 1];
            
            % If only two rows are requested, then exit
            if order < 3
                return
            end
            
            for r = 3 : order
                % The first element of every row is always 1
                triangle(r, 1) = 1;
                
                % Every element is the addition of the two elements
                % on top of it. That means the previous row.
                for c = 2 : r-1
                    triangle(r, c) = triangle(r-1, c-1) + triangle(r-1, c);
                end
                
                % The last element of every row is always 1
                triangle(r, r) = 1;
            end
            
            triangle = triangle(order,:);
        end
    end
end


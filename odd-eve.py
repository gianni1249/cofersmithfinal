
numbers = [5, 1, 4, 8, 12, 7, 4, 9, 11, 14, 32, 2, 7, 12]

def Split(mix): 
        even = [] 
        odd = [] 
        for i in mix: 
            if (i % 2 == 0): 
                even.append(i) 
            else: 
                odd.append(i) 
        print("Even: ", even) 
        print("Odd: ", odd) 

Split(numbers)

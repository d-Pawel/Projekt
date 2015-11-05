import sys 
import os.path 
 
if __name__ == "__main__": 
    
    #if len(sys.argv) != 2: 
    print("usage: create_csv <base_path>") 
        #sys.exit(1) 
    
    #BASE_PATH=sys.argv[1]
    BASE_PATH=os.path.dirname(os.path.abspath(__file__))
    #print (BASE_PATH)
    #name = input ("Podaj nazwe folderu ze zdjeciami: ")
    BASE_PATH = BASE_PATH + '\images'
    print (BASE_PATH)
    f = open('faces.csv', 'w+')
    label = 0 
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames: 
            subject_path = os.path.join(dirname, subdirname) 
            for filename in os.listdir(subject_path): 
                abs_path = "%s/%s" % (subject_path, filename) 
                f.write(abs_path + ";" + str(label)+ "\n") 
            label = label + 1

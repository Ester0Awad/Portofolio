words = set()
# that will give me a hash table with key (or) value 

def check(word):
    if word.lower() in words:
        return True
    else:
        return False




def load(word):
    file = open(dictionary, "r")
    for line in file:
        word = line.rstrip()
        words.add(word)
    close(file)
    return True




def size():
    return len(words)





def unload():
    return True

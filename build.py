import os

def build():
    os.system("cd build && cmake .. && make && ./tpzq")

if __name__ == "__main__":
    if os.path.exists('./build'):
        build()
    else:
        os.system('mkdir build')
        build()

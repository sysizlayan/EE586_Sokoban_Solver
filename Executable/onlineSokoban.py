from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
import selenium.webdriver
import time
import numpy as np
import os
import msvcrt as m

address = input("Please enter the link:")
algorithm = input("Please enter the algorithm\ne: BFS\nt: IDDFS\ny: Deadlock\nu: Manhattan\ni: Euclidean\no: Manhattan and Deadlock\np: Deadlock Checking BFS\n")
if(algorithm is not 'e' and algorithm is not 't' and algorithm is not 'y' and algorithm is not 'u' and algorithm is not 'i' and algorithm is not 'o' and algorithm is not 'p'):
	print("WRONG ALGORTIHM!\n")
	algorithm = input("Please enter the algorithm\ne: BFS\nt: IDDFS\ny:Deadlock\nu:Manhattan\ni: Euclidean\no: Manhattan and Deadlock\np:Deadlock Checking BFS\n")

driver = webdriver.Chrome()
# driver.get("file:///C:/Users/Yigit/Desktop/Dropbox/EE586/code/GUI/game.html")
#driver.get("http://www.game-sokoban.com/index.php?mode=level&lid=53&version=4")
driver.get(address)
time.sleep(1)
content = driver.page_source
file_object  = open('sokobanGame.txt', "w")
# content = file_object.read()
whole_html = BeautifulSoup(content,'html.parser')
# file_object.close()

game_outer_x = driver.find_element_by_id('tb4').location['x']
game_outer_y = driver.find_element_by_id('tb4').location['y']

player_outer_x = driver.find_element_by_id('mv1').location['x']
player_outer_y = driver.find_element_by_id('mv1').location['y']
player_size = driver.find_element_by_id('mv1').size['height']

player_pos_y = int(( player_outer_y-game_outer_y)/(player_size+1))
player_pos_x= int(( player_outer_x-game_outer_x)/(player_size+1))

# print(player_pos_x,player_pos_y)

boxes = driver.find_elements_by_class_name('bx1')
box_position_list = []
for box in boxes[0:len(boxes)-1]:
    box_x = box.location['x']
    box_y = box.location['y']
    box_pos_y = int((box_y - game_outer_y) / (player_size + 1))
    box_pos_x = int((box_x - game_outer_x) / (player_size + 1))
    box_position_list.append({'x':box_pos_x,'y':box_pos_y})

game_div = whole_html.find("div", {"id": "tb1"})
game_table = game_div.find("table", {"id": "tb4"})
game_table_char = []

i=0
j=0

for row in game_table.find_all_next('tr'):
    row_str = ""
    j=0
    for col in row.contents:
        try:
            if(col['class'][0] is ""):
                row_str = row_str + " "
            elif(col['class'][0].find('wall') is not -1):
                row_str = row_str + "#"
            elif (col['class'][0].find('floor') is not -1):
                row_str = row_str + " "
            elif (col['class'][0].find('aim') is not -1):
                row_str = row_str + "."
        except:
            row_str = row_str + " "

        if(player_pos_x == j and player_pos_y == i):
            if (row_str[j] == '.'):
                new = list(row_str)
                new[j] = '+'
                row_str = ''.join(new)
            else:
                new = list(row_str)
                new[j] = '@'
                row_str = ''.join(new)
        for k in range(len(boxes)-1):
            if(box_position_list[k]['x'] == j and box_position_list[k]['y'] == i):
                if(row_str[j] == '.'):
                    new = list(row_str)
                    new[j] = '*'
                    row_str = ''.join(new)
                else:
                    new = list(row_str)
                    new[j] = '$'
                    row_str = ''.join(new)

        j = j+1
    if row_str != "                    ":
        game_table_char.append(list(row_str))
    i = i+1

game_table_T = np.array(game_table_char).transpose()
compare_str = np.array([[' '] * game_table_T.shape[1]])

game_table_T_T = []
for game_row in game_table_T:
    if(np.array_equal(game_row,compare_str[0]) is False):
        game_table_T_T.append(game_row)
        # game_table.append(str(''.join(list(asd))))
game_table = np.array(game_table_T_T).transpose()
file_object.write(str(game_table.shape[0]))
file_object.write(' ')
file_object.write(str(game_table.shape[1]))
file_object.write('\n')

for rowss in game_table:
    file_object.write(''.join(rowss))
    file_object.write('\n')
    print(''.join(rowss))
file_object.close()
os.system('ee586.exe sokobanGame.txt ' + algorithm)

solution_file = open("result.txt")
solution_time = int(solution_file.readline())
solution_steps = int(solution_file.readline())

solution_file.readline()
for line in solution_file:
    keyy = Keys.LEFT
    print(line)
    acc = ActionChains(driver)
    if(line[0] == 'l'):
        keyy = Keys.LEFT
    elif(line[0] == 'r'):
        keyy = Keys.RIGHT
    elif (line[0] == 'u'):
        keyy = Keys.UP
    elif (line[0] == 'd'):
        keyy = Keys.DOWN
    acc.send_keys(keyy).perform()
    time.sleep(0.7)
print('Time:')
print(solution_time)
print('Steps:')
print(solution_steps)
time.sleep(5)
m.getch()
driver.quit()
exit()

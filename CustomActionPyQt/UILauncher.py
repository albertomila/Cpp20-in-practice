import sys
import git
#from PyQt5 import QtGui
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication
#from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QDialog
from git import Repo


DIR_NAME = "C:\Git\Formation"
REMOTE_URL = "https://albertomila@bitbucket.org/albertomila/formation.git"

class CWindow(QDialog):
    def __init__(self):
        super().__init__()
        uic.loadUi("testPyQT.ui", self)

        repo = Repo.init(DIR_NAME)

        headcommit = repo.head.commit
        print(headcommit)
        print(headcommit.parents)
        print(headcommit.tree.type)
        print(headcommit.author.name)
        print(headcommit.authored_date)
        print(headcommit.committer.name)
        print(headcommit.committed_date)
        print(headcommit.message)


        commit_user = ""

        fifty_first_commits = list(repo.iter_commits('master', max_count=50))
        for entry in fifty_first_commits:
            print(entry.hexsha)
            if entry.hexsha == "8d90a725f35e419a992611b4776b68312082f4e0":
                commit_user = entry.author
                break;

        for entry in fifty_first_commits:
            if entry.author == commit_user:
                print(entry.hexsha)



app = QApplication(sys.argv)
g_window = CWindow()
g_window.show()

app.exec_()
sys.exit(app)
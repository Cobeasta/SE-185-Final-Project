This is the final project for our SE185 group.


SET UP GIT BASH ON YOUR COMPUTER, ALSO HAS THE COMMANDS TO DO WHAT YOU NEED WITH GIT

Download git bash from the following link: https://gitforwindows.org/

Launch git bash
Use cd to change to whatever directory you wish to clone the project folder into.
git clone https://github.com/Cobeasta/SE-185-Final-Project.git
git branch {name}
git checkout {name}
## Make changes to your code
git add * 
#add all files to git
git commit -m " {Describe whatever changes you made}"
git push
#add your changes to the branch on the remote repo

PROCESS FOR MAKING CHANGES TO THE CODE

1. Clone the repository locally - this creates a local copy of the project on your computer.
2. Create a branch from the master branch - this creates a working copy to make changes for. Use branches for small changes in the code.
3. Add any new files to git and commit whatever changes you make to this branch. If a branch takes multiple days make sure to push your progress to the remote repo.
4.  create a pull request once you are finished.
5. Someone will review the pull request and merge the branch with master after making sure the changes work.
6. Once the branch is merged, remove it and make a new one for your next issue.
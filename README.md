<div align="center">

# **pomo 🍅 time**

simple pomodoro timer made with [wxWidgets](https://www.wxwidgets.org/)

![demo](https://github.com/cindyhalim/pomotime/blob/master/docs/demo.png)

</div>

<br/>

### **motivation:**

- first attempt at building something with C++

  <br/>

### **features:**

- start, stop/pause, and skip to next task ⏩
- tasks: ⏲
  - **working time (pomodoro)**: 25 minutes
  - **short break**: 5 minutes
  - **long break**: 15 minutes
- cycle composed of 4 intervals of pomodoro + short break and 1 interval of pomodoro + long break 🚴
- calming notification on task end 😌

<br/>

### **setup:**

- clone this repo with the recursive flag: `git clone REPO_URL --recursive`. this will initialize the repo and update submodules. alternatively, you can run:

```
git clone REPO_URL
git submodule update --init --recursive
```

- **build**: in root directory, run `cmake -S . -B build/`
- **configure**: cd to `build` directory, and run `make -j 16` (16 threads to speed up the compilation process)
- **run**: cd to `build` and run `./pomotime`
- the above commands are provided in shell scripts. run `chmod +x ./build.sh ./configure.sh ./run.sh` to allow access

<br/>

### **improvements:**

- coming up: performance + memory leak check
- ability to edit/customize time

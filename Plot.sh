# Plotting figures
# Execute this to plot figures
for((function=1;function<3;function++))
do
    ./bin/main 10 ${function}
    chmod 755 Gnuplot.sh
    ./Gnuplot.sh
done

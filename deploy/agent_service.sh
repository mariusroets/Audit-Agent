
RETVAL=0

start()
{
    echo "Starting Lattitude Audit Agent "
    echo " log location is:" $logdir
    "$prefix/$installdir/agent" -d start >> "$logdir/$servicelog"
    echo "Done starting Lattitude Audit Agent! "

}

stop()
{
    echo "Stopping Lattitude Audit Agent "
    "$prefix/$installdir/agent" -d stop >> "$logdir/$servicelog"
    echo "Done stopping Lattitude Audit Agent! "
}

# See how we were called.
case "$1" in
    start)
        start
    ;;
    stop)
        stop
    ;;
    status)
        status -p $pidfile $processname
        RETVAL=$?
    ;;
    restart)
        stop
        start
    ;;
    condrestart)
        if [ -f /var/lock/subsys/$servicename ]; then
            stop
            start
        fi
    ;;
    *)
        echo $"Usage: $0 {start|stop|status|restart|condrestart}"
    ;;
esac
exit $RETVAL


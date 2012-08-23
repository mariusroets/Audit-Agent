
RETVAL=0

start()
{
    echo "Starting Lattitude Audit Agent "
    echo " log location is:" $logdir
    "$prefix/$installdir/agent" -d start
    echo "Done starting Lattitude Audit Agent! "

}

stop()
{
    echo "Stopping Lattitude Audit Agent "
    "$prefix/$installdir/agent" -d stop
    echo "Done stopping Lattitude Audit Agent! "
}
status()
{
    echo "Determining status of Lattitude Audit Agent "
    "$prefix/$installdir/agent" -d status
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
        status
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


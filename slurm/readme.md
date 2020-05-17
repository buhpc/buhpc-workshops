# Slurm Tutorial

## checking system resources
`sinfo`

* displays node/partition info

## submit a job
`srun --nodes=2 --ntaks=1 --cpus-per-task=1 --batch run_gromacs.sh`

* `run_gromacs.sh` is a bash file giving configuration and execution details

## display queue info
`squeue`

## cancel a job
`scancel 12345`
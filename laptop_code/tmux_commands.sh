echo 'PS1=">"' > ~/.bashrc

rm curr_term.log

tmux new-session -s mysession -n mywindow -d
tmux pipe-pane -o "cat >> curr_term.log"
tmux attach-session -t mysession

# probably manually start this
# python3 term_state.py


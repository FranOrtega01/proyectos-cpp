#include "StateMachine.h"

// void StateMachine::addState( StateRef newState, bool isReplacing){
//     _isAdding = true;
//     _isReplacing = isReplacing;

//     _newState = std::move( newState );
// }

// void StateMachine::removeState(){
//     _isRemoving = true;
// }


// void StateMachine::processStateChanges(){
//     if(_isRemoving && !_states.empty()){
//         _states.pop();
//         if(!_states.empty()){
//             _states.top()->resume();
//         }
//         _isRemoving = false;
//     }

//     if(_isAdding){
//         if(!_states.empty()){
//             if(_isReplacing){
//                 _states.pop();
//             }else{
//                 _states.top()->pause();
//             }
//         }
//         _states.push(std::move(_newState));
//         _states.top();
//         _isAdding = false;
//     }
// }


// StateRef &StateMachine::getActiveState(){
//     return _states.top();
// }

void StateMachine::addState(StateRef newState) {
    // Si hay un estado activo, pausarlo (opcional, según tus necesidades)
    if (!states.empty()) {
        states.top()->pause();
    }

    // Agregar el nuevo estado al stack
    states.emplace(std::move(newState));
}

void StateMachine::removeState() {
    // Si hay estados en el stack, pop el estado activo
    if (!states.empty()) {
        states.pop();
    }

    // Si después de hacer pop hay un estado activo, resumirlo (opcional, según tus necesidades)
    if (!states.empty()) {
        states.top()->resume();
    }
}

StateRef &StateMachine::getActiveState() {
    // Devolver el estado activo (puede necesitar manejo de errores si el stack está vacío)
    return states.top();
}
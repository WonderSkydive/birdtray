// Test the JavaScript embedded in the C++ backend against simulated KWin windows.
const assert = require('node:assert/strict');
const fs = require('node:fs');
const vm = require('node:vm');
const path = require('node:path');
const source = fs.readFileSync(path.join(__dirname, '../../src/windowtools_kwin.cpp'), 'utf8');
const script = source.split('R"JS(')[1].split(')JS"')[0];
const workspace = { windows: [], activeWindow: null, windowList() { return this.windows; } };
const mail = { internalId:'mail', normalWindow:true, resourceClass:'thunderbird',
    caption:'Inbox — Mozilla Thunderbird', minimizable:true, closeable:true,
    skipTaskbar:false, skipPager:true, minimized:false, closeWindow(){ this.closed = true; } };
const compose = {...mail, internalId:'compose', caption:'Write: message'};
const browser = {...mail, internalId:'web', resourceClass:'firefox'};
workspace.windows = [browser,compose,mail];
workspace.activeWindow = compose;
function run(operation, previous={}, hideWhenMinimized=false, configured='thunderbird') {
    let result;
    const a = [operation, ':1.10', '/Birdtray/KWinResult', 'test-token',
        previous.id || '', configured, previous.skipTaskbar || false,
        previous.skipPager || false, hideWhenMinimized, 'Mozilla Thunderbird'];
    vm.runInNewContext('const a = '+JSON.stringify(a)+script,{workspace,callDBus(...args){
        assert.equal(args[4],'test-token');
        result = JSON.parse(args[5]);
    }});
    return result;
}
let state = run('probe');
assert.equal(state.id,'mail');
state = run('hide',state);
assert.equal(state.hidden,true);
assert.equal(state.skipTaskbar,false);
assert.equal(state.skipPager,true);
assert.equal(browser.minimized,false);
assert.equal(compose.minimized,false);
state = run('show',state);
assert.equal(state.minimized,false);
assert.equal(mail.skipTaskbar,false);
assert.equal(mail.skipPager,true);
assert.equal(workspace.activeWindow,mail);
mail.minimized = true;
state = run('probe',state,true);
assert.equal(state.hidden,true);
mail.minimized = false; // External activation (e.g. notification).
state = run('probe',state);
assert.equal(state.hidden,false);
assert.equal(mail.skipTaskbar,false);
assert.equal(mail.skipPager,true);
state = run('hide',state);
state = run('close',state);
assert.equal(mail.closed,true);
assert.equal(mail.skipTaskbar,false);
assert.equal(mail.skipPager,true);
workspace.windows = [browser,compose];
assert.equal(run('hide',state).found,false);
assert.equal(compose.minimized,false);
workspace.windows = [browser];
assert.equal(run('probe',{},false,'thunderbird"; throw "not code').found,false);
console.log('KWin script simulation: window selection, hide, restore, auto-hide, external activation, close and stale window checks passed');

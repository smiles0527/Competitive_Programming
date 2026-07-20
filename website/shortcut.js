function moveProblem(direction) {
  const picker = document.getElementById('editorial');
  if (!picker) return false;

  const nextIndex = picker.selectedIndex + direction;
  if (nextIndex < 0 || nextIndex >= picker.options.length) return false;

  picker.selectedIndex = nextIndex;
  picker.dispatchEvent(new Event('change'));
  return true;
}

const theme = document.createElement('link');
theme.rel = 'stylesheet';
theme.href = new URL('../../website/editorial-theme.css', location.href).href;
document.head.appendChild(theme);

const editorialPicker = document.getElementById('editorial');
if (editorialPicker?.value) {
  history.replaceState(null, '', `?${new URLSearchParams({ file: editorialPicker.value })}`);
}

const paneLabel = document.querySelector('.code-pane .pane-label');
const sourceCode = document.getElementById('source-code');

if (paneLabel && sourceCode) {
  const copyButton = document.createElement('button');
  copyButton.type = 'button';
  copyButton.className = 'copy-code';
  copyButton.textContent = 'Copy';
  copyButton.setAttribute('aria-label', 'Copy C++ solution');
  paneLabel.appendChild(copyButton);

  copyButton.addEventListener('click', async () => {
    try {
      if (navigator.clipboard) {
        await navigator.clipboard.writeText(sourceCode.textContent);
      } else {
        const field = document.createElement('textarea');
        field.value = sourceCode.textContent;
        field.style.position = 'fixed';
        field.style.opacity = '0';
        document.body.appendChild(field);
        field.select();
        document.execCommand('copy');
        field.remove();
      }
      copyButton.textContent = 'Copied';
      setTimeout(() => { copyButton.textContent = 'Copy'; }, 1400);
    } catch {
      copyButton.textContent = 'Copy failed';
      setTimeout(() => { copyButton.textContent = 'Copy'; }, 1400);
    }
  });
}

addEventListener('keydown', event => {
  const commandKey = event.ctrlKey || event.metaKey;
  if (commandKey && event.shiftKey && event.key.toLowerCase() === 'e') {
    event.preventDefault();
    parent.postMessage({ type: 'open-editor' }, location.origin);
    return;
  }

  if (commandKey && (event.key === 'ArrowUp' || event.key === 'ArrowDown')) {
    if (moveProblem(event.key === 'ArrowUp' ? -1 : 1)) event.preventDefault();
  }
});

addEventListener('message', event => {
  if (event.origin !== location.origin || event.data?.type !== 'move-problem') return;
  moveProblem(event.data.direction);
});

#!/usr/bin/env python3
"""Create a standard Birdtray package without installing or running it."""
from pathlib import Path
import os, subprocess, sys, shutil, tempfile, hashlib
source = Path(__file__).resolve().parents[1]
build = Path(sys.argv[1]).resolve()
out = Path(sys.argv[2]).resolve()
with tempfile.TemporaryDirectory(prefix='birdtray-package-',dir=build.parent) as directory:
    stage=Path(directory)
    environment=os.environ.copy()
    environment['DESTDIR']=str(stage)
    subprocess.run(['cmake','--install',str(build),'--prefix','/usr'],env=environment,check=True)
    control=stage/'DEBIAN'
    control.mkdir()
    shutil.copy2(source/'local-packaging/control',control/'control')
    doc=stage/'usr/share/doc/birdtray'
    doc.mkdir(parents=True)
    shutil.copy2(source/'LICENSE.txt',doc/'copyright')
    shutil.copy2(source/'local-packaging/CHANGES.md',doc/'CHANGES.md')
    for path in stage.rglob('*'):
        path.chmod(0o755 if path.is_dir() or path==stage/'usr/bin/birdtray' else 0o644)
    files=sorted(p for p in (stage/'usr').rglob('*') if p.is_file())
    (control/'md5sums').write_text(''.join(hashlib.md5(p.read_bytes()).hexdigest()+'  '+str(p.relative_to(stage))+'\n' for p in files))
    subprocess.run(['dpkg-deb','--root-owner-group','--build',str(stage),str(out)],check=True)

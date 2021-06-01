import { Component, OnInit } from '@angular/core';

import { MainService } from '../main.service';
import { Log } from '../log'

@Component({
  selector: 'app-showalllogs',
  templateUrl: './showalllogs.component.html',
  styleUrls: ['./showalllogs.component.css']
})
export class ShowalllogsComponent implements OnInit {
  logs: Log[] = [];

  constructor(private mainService: MainService) { }

  ngOnInit(): void {
    this.getAllLogs();
  }

  getAllLogs(): void {
    this.mainService
      .getAllLogs()
      .subscribe(logs => {console.log(logs); this.logs = logs});
  }
}

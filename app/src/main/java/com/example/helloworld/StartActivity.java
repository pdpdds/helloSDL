package com.example.helloworld;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;

import android.util.Log;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;

public class StartActivity  extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        checkPermission();
    }


    private void checkPermission() {
        // if SDK level > 23 then check permission
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {

            int i = ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE);

            if (i != PackageManager.PERMISSION_GRANTED) {

                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
            }
            else {
                startGame();
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode) {
            case 1: {
                // If request is cancelled, the result arrays are empty.
                for (int i = 0; i < permissions.length; i++) {
                    String p = permissions[i];

                    if (p.equals(Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                        Log.d("helloSDL", "WRITE_EXTERNAL_STORAGE : " + grantResults[i]);
                        if (grantResults[i] == PackageManager.PERMISSION_GRANTED) {
                            startGame();
                        }
                        else if (ActivityCompat.shouldShowRequestPermissionRationale((Activity) this, p)) {
                            Toast.makeText(this, "쓰기 권한을 허용해 주세요", Toast.LENGTH_SHORT).show();
                        }
                    }
                }

                break;

            }
        }
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    void startGame()
    {
        startActivity(new Intent(this, MyGame.class));
    }
}
